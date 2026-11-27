// No Copyright.

#include "AbilitySystem/Abilities/FireAbilities/FireBoltAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystem/AbilityTask/AbilityTask_TargetDataUnderMouse.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "GameplayTags/AuraGameplayTags.h"

void UFireBoltAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	check(FireboltMontage);
	
	UAbilityTask_TargetDataUnderMouse* TargetDataUnderMouseTask =
		UAbilityTask_TargetDataUnderMouse::CreateTargetDataUnderMouse(this);
	
	TargetDataUnderMouseTask->ValidData.AddDynamic(this, &UFireBoltAbility::OnTargetDataReceived);
	TargetDataUnderMouseTask->ReadyForActivation();
	
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

void UFireBoltAbility::OnTargetDataReceived(const FGameplayAbilityTargetDataHandle& TargetData)
{
	const FGameplayAbilityTargetData* Data = TargetData.Get(0);
	const FHitResult* HitResult = Data ? Data->GetHitResult() : nullptr;
	if (!HitResult)
	{
		UE_LOG(LogTemp, Warning, TEXT("[FireBolt] OnTargetDataReceived: no hit result in target data"));
		return;
	}
	
	// Server = red, client = green. On a listen server / standalone you'll only see red.
	const bool bIsServer = HasAuthority(&CurrentActivationInfo);
	const FColor DebugColor = bIsServer ? FColor::Red : FColor::Green;
	const TCHAR* NetRole = bIsServer ? TEXT("Server") : TEXT("Client");
	const AActor* HitActor = HitResult->GetActor();
	
	UE_LOG(LogTemp, Log, TEXT("[FireBolt][%s] Target: %s | Location: %s | Blocking: %d"),
		NetRole,
		HitActor ? *HitActor->GetName() : TEXT("None"),
		*HitResult->ImpactPoint.ToString(),
		HitResult->bBlockingHit);
	
	if (const UWorld* World = GetWorld())
	{
		DrawDebugSphere(World, HitResult->ImpactPoint, 20.f, 12, DebugColor, false, 3.f);
	}
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, DebugColor,
			FString::Printf(TEXT("[FireBolt][%s] %s @ %s"),
				NetRole,
				HitActor ? *HitActor->GetName() : TEXT("None"),
				*HitResult->ImpactPoint.ToString()));
	}
}
