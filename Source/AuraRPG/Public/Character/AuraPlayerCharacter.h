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
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Aura|Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = "Aura|Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
};
