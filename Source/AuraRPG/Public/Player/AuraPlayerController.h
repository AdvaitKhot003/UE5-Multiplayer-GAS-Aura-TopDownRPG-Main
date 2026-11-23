// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UAuraInputDataAsset;
class IEnemyInterface;
class UAuraAbilitySystemComponent;
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
};
