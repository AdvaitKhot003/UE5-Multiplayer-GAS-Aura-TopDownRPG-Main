// No Copyright.

#include "AbilitySystem/Abilities/ProjectileSpellAbility.h"
#include "Actor/ProjectileActorBase.h"
#include "Interface/CombatInterface.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"

void UProjectileSpellAbility::SpawnProjectile()
{
	check(ProjectileActorClass);
	
	const bool bIsServer = HasAuthority(&CurrentActivationInfo);
	if (!bIsServer && !IsLocallyControlled()) return; // only the server and the local client spawn
	
	const ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (!CombatInterface) return;
	const FVector SocketLocation = CombatInterface->GetCombatWeaponSocketLocation();
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	
	AProjectileActorBase* Projectile = GetWorld()->SpawnActorDeferred<AProjectileActorBase>(ProjectileActorClass,
		SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetAvatarActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	
	if (!Projectile) return;
	Projectile->bIsClient = !bIsServer; // set before FinishSpawning so BeginPlay sees it
	
	if (Projectile->bIsClient)
	{
		Projectile->SetReplicates(false);
		Projectile->SetReplicateMovement(false);
	}
	
	Projectile->FinishSpawning(SpawnTransform);
}
