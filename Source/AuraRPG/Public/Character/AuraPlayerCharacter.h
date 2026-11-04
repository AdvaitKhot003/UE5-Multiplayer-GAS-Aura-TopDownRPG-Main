// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class AURARPG_API AAuraPlayerCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
	
public:
	AAuraPlayerCharacter();
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
#pragma region Ability System Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
#pragma endregion
	
protected:
	virtual void InitAbilityCharacterInfo() override;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Aura|Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = "Aura|Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
};
