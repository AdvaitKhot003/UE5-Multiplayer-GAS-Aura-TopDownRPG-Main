// No Copyright.

#include "AssetManager/AuraAssetManager.h"

UAuraAssetManager& UAuraAssetManager::GetAuraAssetManager()
{
	check(GEngine);
	UAuraAssetManager* AuraAssetManager = CastChecked<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
}
