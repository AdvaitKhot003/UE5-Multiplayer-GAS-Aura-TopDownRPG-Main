// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UAuraInputDataAsset;
class USplineComponent;
class UAuraAbilitySystemComponent;
class IEnemyInterface;
struct FInputActionValue;

UCLASS()
class AURARPG_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();
	
	virtual void PlayerTick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Aura|DataAsset")
	TObjectPtr<UAuraInputDataAsset> AuraInputDataAsset;
	
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;
	
	UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent();
	
	void Move(const FInputActionValue& InputActionValue);
	
	void AbilityInputPressed(FGameplayTag InInputTag);
	void AbilityInputHeld(FGameplayTag InInputTag);
	void AbilityInputReleased(FGameplayTag InInputTag);
	
	UPROPERTY(Transient)
	FHitResult CursorHitResult;
	
	UPROPERTY(Transient)
	TScriptInterface<IEnemyInterface> LastHitResultActor;
	
	UPROPERTY(Transient)
	TScriptInterface<IEnemyInterface> ThisHitResultActor;
	
	void TraceUnderCursor();
	void ClickToRun();
	void AutoRun();
	bool BuildAutoRunPath();
	
	UPROPERTY(Transient)
	FVector CachedDestination = FVector::ZeroVector;
	
	UPROPERTY(Transient)
	bool bAutoRunning = false;
	
	UPROPERTY(Transient)
	bool bTargeting = false;
	
	UPROPERTY(Transient)
	float PressTime = 0.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Movement")
	float ShortPressThreshold = 0.3f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Movement")
	float AutoRunAcceptanceRadius = 50.f;
	
	UPROPERTY(VisibleAnywhere, Category = "Aura|Movement")
	TObjectPtr<USplineComponent> Spline;
};
