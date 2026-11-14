// No Copyright.

#include "UI/UserWidget/ProgressBar/GlobeProgressBarWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "UI/WidgetController/OverlayWidgetController.h"

void UGlobeProgressBarWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (!Image_GlobeRing || !Image_GlobeGlass || !ProgressBar_Globe || !ProgressBar_Ghost) return;
	
	Image_GlobeRing->SetBrush(GlobeRingBrush);
	Image_GlobeGlass->SetBrush(GlobeGlassBrush);
	
	FProgressBarStyle GlobeBarStyle;
	GlobeBarStyle.SetBackgroundImage(FSlateNoResource());
	GlobeBarStyle.SetFillImage(GlobeBarFillBrush);
	GlobeBarStyle.SetMarqueeImage(FSlateNoResource());
	ProgressBar_Globe->SetWidgetStyle(GlobeBarStyle);
	
	FProgressBarStyle GhostBarStyle;
	GhostBarStyle.SetBackgroundImage(FSlateNoResource());
	GhostBarStyle.SetFillImage(GhostBarFillBrush);
	GhostBarStyle.SetMarqueeImage(FSlateNoResource());
	ProgressBar_Ghost->SetWidgetStyle(GhostBarStyle);
}

void UGlobeProgressBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (!ProgressBar_Ghost) return;
	
	const float GhostPercentCurrent = ProgressBar_Ghost->GetPercent();
	if (FMath::IsNearlyEqual(GhostPercentCurrent, GhostPercentTarget)) return;
	
	const float GhostPercentNext = FMath::FInterpTo(GhostPercentCurrent, GhostPercentTarget, InDeltaTime, GhostInterpSpeed);
	SetProgressBarGhostPercent(GhostPercentNext);
}

void UGlobeProgressBarWidget::NativeDestruct()
{
	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ProgressBarTimerHandle);
	}
	Super::NativeDestruct();
}

void UGlobeProgressBarWidget::WidgetControllerSet_Implementation()
{
	if (!WidgetController) return;
	OverlayWidgetController = Cast<UOverlayWidgetController>(WidgetController);
}

void UGlobeProgressBarWidget::SetProgressBarGlobePercent(float Percent)
{
	if (!ProgressBar_Globe) return;
	ProgressBar_Globe->SetPercent(Percent);
	
	if (!bHasReceivedInitialValue)
	{
		bHasReceivedInitialValue = true;
		GhostPercentTarget = Percent;
		SetProgressBarGhostPercent(Percent);
		return;
	}
	
	const UWorld* World = GetWorld();
	if (!World) return;
	
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &UGlobeProgressBarWidget::OnProgressBarGlobePercentSet, Percent);
	
	World->GetTimerManager().SetTimer(ProgressBarTimerHandle, TimerDelegate, GhostTargetDelay, false);
}

void UGlobeProgressBarWidget::OnProgressBarGlobePercentSet(float Percent)
{
	GhostPercentTarget = Percent;
}

void UGlobeProgressBarWidget::SetPercentValue(float NewValue)
{
	PercentValue = NewValue;
	bHasPercentValue = true;
	UpdatePercent();
}

void UGlobeProgressBarWidget::SetPercentMaxValue(float NewValue)
{
	PercentMaxValue = NewValue;
	bHasPercentMaxValue = true;
	UpdatePercent();
}

void UGlobeProgressBarWidget::UpdatePercent()
{
	if (!bHasPercentValue || !bHasPercentMaxValue || PercentMaxValue <= 0.f) return;
	SetProgressBarGlobePercent(FMath::Clamp(PercentValue / PercentMaxValue, 0.f, 1.f));
}

void UGlobeProgressBarWidget::SetProgressBarGhostPercent(float Percent) const
{
	if (!ProgressBar_Ghost) return;
	ProgressBar_Ghost->SetPercent(Percent);
}
