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
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Projectile")
	TSubclassOf<AProjectileActorBase> ProjectileActorClass;
	
	void SpawnProjectile();
};
