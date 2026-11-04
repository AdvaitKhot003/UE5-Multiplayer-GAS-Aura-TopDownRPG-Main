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
	
#pragma region Enemy Interface
	virtual void HighlightEnemy() override;
	virtual void UnhighlightEnemy() override;
#pragma endregion
};
