// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

UINTERFACE()
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

class AURARPG_API IEnemyInterface
{
	GENERATED_BODY()

public:
	virtual void HighlightEnemy() = 0;
	virtual void UnhighlightEnemy() = 0;
};
