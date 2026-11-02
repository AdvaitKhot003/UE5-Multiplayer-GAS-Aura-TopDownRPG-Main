// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

UCLASS()
class AURARPG_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UAuraAssetManager& GetAuraAssetManager();
	
	virtual void StartInitialLoading() override;
};
