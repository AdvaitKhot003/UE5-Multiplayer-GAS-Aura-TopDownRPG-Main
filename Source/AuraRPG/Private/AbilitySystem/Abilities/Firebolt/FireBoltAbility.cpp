// No Copyright.

#include "AbilitySystem/Abilities/FireAbilities/FireBoltAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameplayTags/AuraGameplayTags.h"

void UFireBoltAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	check(FireboltMontage);
	
	UAbilityTask_WaitGameplayEvent* FireBoltEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this, AuraGameplayTags::Event_Ability_FireBolt, nullptr, true);
	
	FireBoltEventTask->EventReceived.AddDynamic(this, &UFireBoltAbility::OnFireBoltEventReceived);
	FireBoltEventTask->ReadyForActivation();
	
	UAbilityTask_PlayMontageAndWait* FireboltMontageTask =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, FireboltMontage);
	
	FireboltMontageTask->OnBlendOut.AddDynamic(this, &UFireBoltAbility::OnFireBoltMontageTaskFinished);
	FireboltMontageTask->OnCompleted.AddDynamic(this, &UFireBoltAbility::OnFireBoltMontageTaskFinished);
	FireboltMontageTask->OnInterrupted.AddDynamic(this, &UFireBoltAbility::OnFireBoltMontageTaskCancelled);
	FireboltMontageTask->OnCancelled.AddDynamic(this, &UFireBoltAbility::OnFireBoltMontageTaskCancelled);
	FireboltMontageTask->ReadyForActivation();
}

void UFireBoltAbility::OnFireBoltMontageTaskFinished()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UFireBoltAbility::OnFireBoltMontageTaskCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UFireBoltAbility::OnFireBoltEventReceived(FGameplayEventData Payload)
{
	SpawnProjectile();
}
