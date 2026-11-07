// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UOverlayWidget;
class UOverlayWidgetController;
class APlayerController;
class APlayerState;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;

UCLASS()
class AURARPG_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& Params);
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Aura|HUD")
	TSubclassOf<UOverlayWidget> OverlayWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|HUD")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
	UPROPERTY(Transient)
	TObjectPtr<UOverlayWidget> OverlayWidget;
	
	UPROPERTY(Transient)
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
};
