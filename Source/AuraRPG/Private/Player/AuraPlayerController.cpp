// No Copyright.

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/AuraEnhancedInputComponent.h"
#include "GameplayTags/AuraGameplayTags.h"

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
	
	AuraEnhancedInputComponent->BindNativeInputAction(AuraInputDataAsset,
		AuraGameplayTags::Input_Move, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisValue = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);
	
	APawn* ControlledPawn = GetPawn<APawn>();
	if (!ControlledPawn) return;
	
	if (!FMath::IsNearlyZero(InputAxisValue.X))
	{
		const FVector RightDirection = YawRotation.RotateVector(FVector::RightVector);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisValue.X);
	}
	
	if (!FMath::IsNearlyZero(InputAxisValue.Y))
	{
		const FVector ForwardDirection = YawRotation.RotateVector(FVector::ForwardVector);
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisValue.Y);
	}
}
