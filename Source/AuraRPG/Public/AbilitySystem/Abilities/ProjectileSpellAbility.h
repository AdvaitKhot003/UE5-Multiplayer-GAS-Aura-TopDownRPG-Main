// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayAbility.h"
#include "ProjectileSpellAbility.generated.h"

class AProjectileActorBase;

UCLASS()
class AURARPG_API UProjectileSpellAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	void SpawnProjectile();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Projectile")
	TSubclassOf<AProjectileActorBase> ProjectileClassToSpawn;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Projectile")
	float EndAbilityDelay = 1.f;
	
	UFUNCTION()
	void OnDelayFinished();
};
