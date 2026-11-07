// No Copyright.

#include "UI/UserWidget/ProgressBar/GlobeProgressBarWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

void UGlobeProgressBarWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (!Image_GlobeRing || !Image_GlobeGlass || !ProgressBar_Globe) return;
	
	Image_GlobeRing->SetBrush(GlobeRingBrush);
	Image_GlobeGlass->SetBrush(GlobeGlassBrush);
	
	FProgressBarStyle GlobeBarStyle;
	GlobeBarStyle.SetBackgroundImage(FSlateNoResource());
	GlobeBarStyle.SetFillImage(GlobeBarFillBrush);
	GlobeBarStyle.SetMarqueeImage(FSlateNoResource());
	ProgressBar_Globe->SetWidgetStyle(GlobeBarStyle);
}

void UGlobeProgressBarWidget::SetProgressBarGlobePercent(float Percent)
{
	if (!ProgressBar_Globe) return;
	ProgressBar_Globe->SetPercent(Percent);
}
