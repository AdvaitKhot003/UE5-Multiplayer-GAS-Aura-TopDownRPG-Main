// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class USkeletalMeshComponent;

UCLASS(Abstract)
class AURARPG_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()
	
public:
	AAuraCharacterBase();
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Aura|Combat")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
};
