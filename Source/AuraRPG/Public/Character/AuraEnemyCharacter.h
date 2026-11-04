// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "Interface/EnemyInterface.h"
#include "AuraEnemyCharacter.generated.h"

UCLASS()
class AURARPG_API AAuraEnemyCharacter : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AAuraEnemyCharacter();
	
	virtual void BeginPlay() override;
	
#pragma region Enemy Interface
	virtual void HighlightEnemy() override;
	virtual void UnhighlightEnemy() override;
#pragma endregion
	
#pragma region Ability System Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
#pragma endregion
	
protected:
	virtual void InitAbilityCharacterInfo() override;
};
