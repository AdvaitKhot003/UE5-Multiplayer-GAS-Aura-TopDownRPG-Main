// No Copyright.

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/AuraEnhancedInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	SetReplicates(true);
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsLocalPlayerController()) return;
	
	check(AuraInputDataAsset);
	
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (!LocalPlayer) return;
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	if (!Subsystem) return;
	
	for (const UInputMappingContext* InputMappingContext : AuraInputDataAsset->InputMappingContexts)
	{
		if (!InputMappingContext) continue;
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
	
	SetShowMouseCursor(true);
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetHideCursorDuringCapture(false);
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	check(AuraInputDataAsset);
	
	UAuraEnhancedInputComponent* AuraEnhancedInputComponent = CastChecked<UAuraEnhancedInputComponent>(InputComponent);
}
