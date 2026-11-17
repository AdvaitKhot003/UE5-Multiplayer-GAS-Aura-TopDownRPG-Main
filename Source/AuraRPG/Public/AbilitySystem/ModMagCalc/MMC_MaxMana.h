// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxMana.generated.h"

UCLASS()
class AURARPG_API UMMC_MaxMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMMC_MaxMana();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
private:
	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|MMC")
	float PreMultiplyAdditive = 0.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|MMC")
	float Coefficient = 2.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|MMC")
	float PostMultiplyAdditive = 60.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|MMC")
	float ManaPerLevel = 10.f;
};
