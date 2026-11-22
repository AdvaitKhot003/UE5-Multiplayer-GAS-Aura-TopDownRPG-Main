// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/UserWidget/Template/AuraSizeBoxWidget.h"
#include "GlobeProgressBarWidget.generated.h"

class UImage;
class UProgressBar;
class UOverlayWidgetController;

UCLASS()
class AURARPG_API UGlobeProgressBarWidget : public UAuraSizeBoxWidget
{
	GENERATED_BODY()
	
public:
	virtual void WidgetControllerSet_Implementation() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|GlobeProgressBar")
	FSlateBrush GlobeRingBrush;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|GlobeProgressBar")
	FSlateBrush GlobeGlassBrush;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|GlobeProgressBar")
	FSlateBrush GlobeBarFillBrush;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|GhostProgressBar")
	FSlateBrush GhostBarFillBrush;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|GhostProgressBar")
	float GhostTargetDelay = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|GhostProgressBar")
	float GhostInterpSpeed = 1.f;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_GlobeRing;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_GlobeGlass;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> ProgressBar_Globe;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> ProgressBar_Ghost;
	
	UPROPERTY(BlueprintReadOnly, Category = "Aura|UserWidget")
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere, Category = "Aura|GlobeProgressBar", meta = (Categories = "Attribute"))
	FGameplayTag AttributeTag;
	
	UPROPERTY(EditAnywhere, Category = "Aura|GlobeProgressBar", meta = (Categories = "Attribute"))
	FGameplayTag MaxAttributeTag;
	
private:
	float PercentValue = 0.f;
	float PercentMaxValue = 0.f;
	float GhostPercentTarget = 0.f;
	
	bool bHasPercentValue = false;
	bool bHasPercentMaxValue = false;
	bool bHasReceivedInitialValue = false;
	
	FTimerHandle ProgressBarTimerHandle;
	
	void SetProgressBarGlobePercent(float Percent);
	void OnProgressBarGlobePercentSet(float Percent);
	
	void SetPercentValue(float NewValue);
	void SetPercentMaxValue(float NewValue);
	void UpdatePercent();
	
	void SetProgressBarGhostPercent(float Percent) const;
	
	void AttributeValueChangeReceived(const FGameplayTag& Tag, float Value);
};
