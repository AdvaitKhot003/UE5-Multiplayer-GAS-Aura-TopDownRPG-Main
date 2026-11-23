// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

class UAuraGameplayAbility;

DECLARE_MULTICAST_DELEGATE_OneParam(FGameplayEffectAssetTagsDelegate, const FGameplayTagContainer&);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURARPG_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void InitAbilityActorInfoSet();
	void GiveStartupAbilities(const TArray<TSubclassOf<UAuraGameplayAbility>>& StartupAbilities, float Level = 1.f);
	
	FGameplayEffectAssetTagsDelegate GameplayEffectAssetTagsDelegate;
	
private:
	UFUNCTION(Client, Reliable)
	void GameplayEffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
		const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
