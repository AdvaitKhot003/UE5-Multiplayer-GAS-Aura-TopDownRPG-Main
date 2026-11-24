// No Copyright.

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/AuraEnhancedInputComponent.h"
#include "GameplayTags/AuraGameplayTags.h"
#include "Interface/EnemyInterface.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

AAuraPlayerController::AAuraPlayerController()
{
	SetReplicates(true);
	
	Spline = CreateDefaultSubobject<USplineComponent>("SplineComp");
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

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	if (!IsLocalPlayerController()) return;
	TraceUnderCursor();
	AutoRun();
}

void AAuraPlayerController::TraceUnderCursor()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHitResult);
	
	LastHitResultActor = ThisHitResultActor;
	ThisHitResultActor = nullptr;
	
	if (CursorHitResult.IsValidBlockingHit())
	{
		ThisHitResultActor = CursorHitResult.GetActor();
	}
	
	if (LastHitResultActor == ThisHitResultActor) return;
	
	if (LastHitResultActor) LastHitResultActor->UnhighlightEnemy();
	if (ThisHitResultActor) ThisHitResultActor->HighlightEnemy();
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	check(AuraInputDataAsset);
	
	UAuraEnhancedInputComponent* AuraEnhancedInputComponent = CastChecked<UAuraEnhancedInputComponent>(InputComponent);
	
	AuraEnhancedInputComponent->BindNativeInputAction(AuraInputDataAsset,
		AuraGameplayTags::Input_Move, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	
	AuraEnhancedInputComponent->BindAbilityInputAction(AuraInputDataAsset, this,
		&ThisClass::AbilityInputPressed, &ThisClass::AbilityInputHeld, &ThisClass::AbilityInputReleased);
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

void AAuraPlayerController::AbilityInputPressed(FGameplayTag InInputTag)
{
	if (InInputTag.MatchesTagExact(AuraGameplayTags::Input_LMB))
	{
		bTargeting = ThisHitResultActor != nullptr;
		bAutoRunning = false;
	}
}

void AAuraPlayerController::AbilityInputHeld(FGameplayTag InInputTag)
{
	UAuraAbilitySystemComponent* AuraASC = GetAuraAbilitySystemComponent();
	if (!AuraASC) return;
	
	if (!InInputTag.MatchesTagExact(AuraGameplayTags::Input_LMB))
	{
		AuraASC->OnAbilityInputHeld(InInputTag);
		return;
	}
	
	if (bTargeting)
	{
		AuraASC->OnAbilityInputHeld(InInputTag);
	}
	else
	{
		PressTime += GetWorld()->GetDeltaSeconds();
		ClickToRun();
	}
}

void AAuraPlayerController::AbilityInputReleased(FGameplayTag InInputTag)
{
	UAuraAbilitySystemComponent* AuraASC = GetAuraAbilitySystemComponent();
	if (!AuraASC) return;
	
	if (!InInputTag.MatchesTagExact(AuraGameplayTags::Input_LMB))
	{
		AuraASC->OnAbilityInputReleased(InInputTag);
		return;
	}
	
	if (bTargeting)
	{
		AuraASC->OnAbilityInputReleased(InInputTag);
	}
	else
	{
		const bool bShortPress = PressTime <= ShortPressThreshold;
		PressTime = 0.f;
		if (!bShortPress) return;
		
		bAutoRunning = BuildAutoRunPath();
	}
}

void AAuraPlayerController::ClickToRun()
{
	if (CursorHitResult.IsValidBlockingHit())
	{
		CachedDestination = CursorHitResult.ImpactPoint;
	}
	
	APawn* ControlledPawn = GetPawn<APawn>();
	if (!ControlledPawn) return;
	
	const FVector CurrentLocation = ControlledPawn->GetActorLocation();
	
	FVector WorldDirection = CachedDestination - CurrentLocation;
	WorldDirection.Z = 0.f;
	WorldDirection = WorldDirection.GetSafeNormal();
	
	if (FVector::Dist2D(CachedDestination, CurrentLocation) > AutoRunAcceptanceRadius)
	{
		ControlledPawn->AddMovementInput(WorldDirection);
	}
}

bool AAuraPlayerController::BuildAutoRunPath()
{
	const APawn* ControlledPawn = GetPawn<APawn>();
	if (!ControlledPawn) return false;
	
	UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(
		this, ControlledPawn->GetActorLocation(), CachedDestination);
	
	if (!NavigationPath || NavigationPath->PathPoints.Num() < 2) return false;
	
	Spline->ClearSplinePoints(false);
	
	for (const FVector& PathPointLocation : NavigationPath->PathPoints)
	{
		Spline->AddSplinePoint(PathPointLocation, ESplineCoordinateSpace::World, false);
	}
	
	CachedDestination = NavigationPath->PathPoints.Last();
	Spline->UpdateSpline();
	
	return true;
}

void AAuraPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	
	APawn* ControlledPawn = GetPawn<APawn>();
	if (!ControlledPawn) return;
	
	const FVector LocationOnSpline =
		Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
	
	const FVector DirectionOnSpline =
		Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
	
	ControlledPawn->AddMovementInput(DirectionOnSpline);
	
	if (FVector::Dist(LocationOnSpline, CachedDestination) <= AutoRunAcceptanceRadius)
	{
		bAutoRunning = false;
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraAbilitySystemComponent()
{
	if (!AuraAbilitySystemComponent)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}
