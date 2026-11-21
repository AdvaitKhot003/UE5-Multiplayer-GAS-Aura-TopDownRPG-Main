// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/UserWidget/Template/AuraSizeBoxWidget.h"
#include "TextValueRowWidget.generated.h"

class UTextBlock;
class UValueWidget;
class UAttributeMenuWidgetController;
struct FAuraAttributeInfo;

UCLASS()
class AURARPG_API UTextValueRowWidget : public UAuraSizeBoxWidget
{
	GENERATED_BODY()
	
public:
	virtual void WidgetControllerSet_Implementation() override;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeOnInitialized() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Attribute;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UValueWidget> ValueWidget;
	
	UPROPERTY(BlueprintReadOnly, Category = "Aura|TextValueRow")
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Aura|TextValueRow", meta = (Categories = "Attribute"))
	FGameplayTag AttributeTag;
	
private:
	void AttributeInfoChangeReceived(const FAuraAttributeInfo& AttributeInfo) const;
	void SetAttributeNameAndValue(const FText& AttributeName, float AttributeValue) const;
};
