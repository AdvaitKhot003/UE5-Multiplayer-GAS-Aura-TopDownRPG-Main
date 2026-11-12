// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FGameplayEffectAssetTagsDelegate ,const FGameplayTagContainer&);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURARPG_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void InitAbilityActorInfoSet();
	
	FGameplayEffectAssetTagsDelegate GameplayEffectAssetTagsDelegate;
	
private:
	UFUNCTION(Client, Reliable)
	void GameplayEffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
		const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
