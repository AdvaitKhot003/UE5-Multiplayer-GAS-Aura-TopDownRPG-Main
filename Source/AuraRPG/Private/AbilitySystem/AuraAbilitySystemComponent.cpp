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
