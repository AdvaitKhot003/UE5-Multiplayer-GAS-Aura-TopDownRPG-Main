// No Copyright.

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

namespace
{
	AAuraHUD* GetHUDAndParams(const UObject* WorldContextObject, FWidgetControllerParams& OutParams)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
		if (!PlayerController) return nullptr;
		
		AAuraPlayerState* AuraPlayerState = PlayerController->GetPlayerState<AAuraPlayerState>();
		AAuraHUD* AuraHUD = PlayerController->GetHUD<AAuraHUD>();
		if (!AuraPlayerState || !AuraHUD) return nullptr;
		
		UAbilitySystemComponent* AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
		UAttributeSet* AttributeSet = AuraPlayerState->GetAttributeSet();
		if (!AbilitySystemComponent || !AttributeSet) return nullptr;
		
		OutParams = FWidgetControllerParams(PlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		return AuraHUD;
	}
}

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams Params;
	AAuraHUD* AuraHUD = GetHUDAndParams(WorldContextObject, Params);
	return AuraHUD ? AuraHUD->GetOverlayWidgetController(Params) : nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams Params;
	AAuraHUD* AuraHUD = GetHUDAndParams(WorldContextObject, Params);
	return AuraHUD ? AuraHUD->GetAttributeMenuWidgetController(Params) : nullptr;
}
