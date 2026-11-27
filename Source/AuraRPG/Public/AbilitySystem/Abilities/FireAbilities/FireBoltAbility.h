// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ProjectileSpellAbility.h"
#include "FireBoltAbility.generated.h"

UCLASS()
class AURARPG_API UFireBoltAbility : public UProjectileSpellAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Aura|FireBolt")
	TObjectPtr<UAnimMontage> FireboltMontage;
	
	UFUNCTION()
	void OnFireBoltMontageTaskFinished();
	
	UFUNCTION()
	void OnFireBoltMontageTaskCancelled();
	
	UFUNCTION()
	void OnFireBoltEventReceived(FGameplayEventData Payload);
};
