// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

UCLASS()
class AURARPG_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMMC_MaxHealth();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
private:
	FGameplayEffectAttributeCaptureDefinition VigorDef;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|MMC")
	float PreMultiplyAdditive = 0.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|MMC")
	float Coefficient = 2.5f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|MMC")
	float PostMultiplyAdditive = 72.5f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|MMC")
	float HealthPerLevel = 10.f;
};
