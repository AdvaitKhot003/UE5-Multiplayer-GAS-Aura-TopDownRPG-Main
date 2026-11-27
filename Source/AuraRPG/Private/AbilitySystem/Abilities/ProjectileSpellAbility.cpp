// No Copyright.

#include "AbilitySystem/Abilities/ProjectileSpellAbility.h"
#include "Actor/ProjectileActorBase.h"
#include "Interface/CombatInterface.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"

void UProjectileSpellAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	UAbilityTask_WaitDelay* DelayTask = UAbilityTask_WaitDelay::WaitDelay(this, EndAbilityDelay);
	DelayTask->OnFinish.AddDynamic(this, &UProjectileSpellAbility::OnDelayFinished);
	DelayTask->ReadyForActivation();
	
	SpawnProjectile();
}

void UProjectileSpellAbility::OnDelayFinished()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UProjectileSpellAbility::SpawnProjectile()
{
	check(ProjectileClassToSpawn);
	
	const bool bIsServer = HasAuthority(&CurrentActivationInfo);
	if (!bIsServer && !IsLocallyControlled()) return; // only the server and the local client spawn
	
	const ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (!CombatInterface) return;
	const FVector SocketLocation = CombatInterface->GetCombatWeaponSocketLocation();
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	
	AProjectileActorBase* Projectile = GetWorld()->SpawnActorDeferred<AProjectileActorBase>(ProjectileClassToSpawn,
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
