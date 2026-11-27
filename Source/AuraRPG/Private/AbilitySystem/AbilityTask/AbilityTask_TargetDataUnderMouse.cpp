// No Copyright.

#include "AbilitySystem/AbilityTask/AbilityTask_TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"

UAbilityTask_TargetDataUnderMouse* UAbilityTask_TargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	return NewAbilityTask<UAbilityTask_TargetDataUnderMouse>(OwningAbility);
}

void UAbilityTask_TargetDataUnderMouse::Activate()
{
	if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
	{
		SendMouseCursorData();
	}
	else
	{
		// Server path: the target data comes from the client via a separate RPC,
		// so it can arrive before or after this task activates.
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationKey = GetActivationPredictionKey();
		
		// Listen for this activation's target data (identified by SpecHandle + ActivationKey).
		// Both orderings go through this callback:
		//  - Data arrives later: the ASC fires this delegate when the RPC lands.
		//  - Data arrived earlier: CallReplicatedTargetDataDelegatesIfSet below fires it right away.
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationKey).AddUObject(
			this, &UAbilityTask_TargetDataUnderMouse::OnTargetDataReplicatedCallback);
		
		// If the target data is already cached on the server, broadcast it now.
		// Returns false if it hasn't arrived yet.
		const bool bCalledDelegate =
			AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationKey);
		
		// Data not here yet: keep the task alive and wait for the client's RPC.
		// The delegate bound above will fire when it arrives.
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UAbilityTask_TargetDataUnderMouse::SendMouseCursorData()
{
	// Lets the server accept this client-predicted action under our prediction key
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	// Trace under the cursor on the local client
	const APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	
	// Wrap the hit result in target data
	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);
	
	// The actual RPC: sends the target data to the server
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey
	);
	
	// Broadcast locally so the client can act on the data right away
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

void UAbilityTask_TargetDataUnderMouse::OnTargetDataReplicatedCallback(
	const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
	// The server has received the target data, so clear it from the ASC's cache.
	// Otherwise, it stays stored and could be picked up again by a later
	// CallReplicatedTargetDataDelegatesIfSet for the same SpecHandle + ActivationKey.
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

	// Pass the client's data on to the ability (the ValidData pin in Blueprint).
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
