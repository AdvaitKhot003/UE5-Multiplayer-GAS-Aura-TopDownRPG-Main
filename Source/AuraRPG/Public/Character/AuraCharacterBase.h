// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class USkeletalMeshComponent;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class AURARPG_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAuraCharacterBase();
	
#pragma region Ability System Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const { return nullptr; }
#pragma endregion
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Aura|Combat")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Aura|AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Aura|AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;
	
	virtual void InitAbilityCharacterInfo();
};
