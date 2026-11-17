// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class USkeletalMeshComponent;
class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;

UCLASS(Abstract)
class AURARPG_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
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
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	virtual void InitDefaultAttributes(UAbilitySystemComponent* SourceASC);
	
	void ApplyEffectSpecToSelf(UAbilitySystemComponent* SourceASC,
		const TSubclassOf<UGameplayEffect>& GameplayEffectClass, float Level = 1.f);
};
