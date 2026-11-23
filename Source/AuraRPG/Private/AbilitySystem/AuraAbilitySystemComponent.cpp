// No Copyright.

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::InitAbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::GameplayEffectApplied);
}

void UAuraAbilitySystemComponent::GameplayEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer AssetTags;
	EffectSpec.GetAllAssetTags(AssetTags);
	if (AssetTags.IsEmpty()) return;
	
	GameplayEffectAssetTagsDelegate.Broadcast(AssetTags);
}

void UAuraAbilitySystemComponent::GiveStartupAbilities(
	const TArray<TSubclassOf<UAuraGameplayAbility>>& StartupAbilities, float Level)
{
	if (!IsOwnerActorAuthoritative()) return;
	
	for (const TSubclassOf<UAuraGameplayAbility>& AbilityClass : StartupAbilities)
	{
		if (!AbilityClass) continue;
		FGameplayAbilitySpec AbilitySpec(AbilityClass, Level);
		
		const UAuraGameplayAbility* AuraGameplayAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability);
		if (!AuraGameplayAbility || !AuraGameplayAbility->StartupAbilityTag.IsValid()) continue;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AuraGameplayAbility->StartupAbilityTag);
		
		GiveAbility(AbilitySpec);
	}
}

void UAuraAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	
}

void UAuraAbilitySystemComponent::OnAbilityInputHeld(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;
	
	ABILITYLIST_SCOPE_LOCK();
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;
		AbilitySpecInputPressed(AbilitySpec);
		
		if (AbilitySpec.IsActive())
		{
			const UGameplayAbility* AbilityInstance = AbilitySpec.GetPrimaryInstance();
			if (!AbilityInstance) continue;
			
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, AbilitySpec.Handle,
				AbilityInstance->GetCurrentActivationInfo().GetActivationPredictionKey());
		}
		else
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UAuraAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;
	
	ABILITYLIST_SCOPE_LOCK();
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;
		AbilitySpecInputReleased(AbilitySpec);
		
		if (AbilitySpec.IsActive())
		{
			const UGameplayAbility* AbilityInstance = AbilitySpec.GetPrimaryInstance();
			if (!AbilityInstance) continue;
			
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, AbilitySpec.Handle,
				AbilityInstance->GetCurrentActivationInfo().GetActivationPredictionKey());
		}
	}
}
