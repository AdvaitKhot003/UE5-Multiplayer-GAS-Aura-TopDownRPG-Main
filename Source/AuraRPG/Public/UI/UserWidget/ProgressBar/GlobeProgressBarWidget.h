// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidget/Template/AuraSizeBoxWidget.h"
#include "GlobeProgressBarWidget.generated.h"

class UImage;
class UProgressBar;

UCLASS()
class AURARPG_API UGlobeProgressBarWidget : public UAuraSizeBoxWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|GlobeProgressBar")
	FSlateBrush GlobeRingBrush;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|GlobeProgressBar")
	FSlateBrush GlobeGlassBrush;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|GlobeProgressBar")
	FSlateBrush GlobeBarFillBrush;
	
	UFUNCTION(BlueprintCallable)
	void SetProgressBarGlobePercent(float Percent);
	
protected:
	virtual void NativePreConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_GlobeRing;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_GlobeGlass;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> ProgressBar_Globe;
};
