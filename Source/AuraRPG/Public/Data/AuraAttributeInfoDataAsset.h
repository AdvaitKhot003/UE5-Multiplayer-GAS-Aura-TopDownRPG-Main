// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraAttributeInfoDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, meta = (Categories = "Attribute"))
	FGameplayTag AttributeTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly)
	FText AttributeName = FText();
	
	UPROPERTY(EditDefaultsOnly)
	FText AttributeDescription = FText();
	
	UPROPERTY(Transient)
	float AttributeValue = 0.f;
	
	bool IsValid() const { return AttributeTag.IsValid() && !AttributeName.IsEmpty(); }
};

UCLASS()
class AURARPG_API UAuraAttributeInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Attributes", meta = (TitleProperty = "AttributeName"))
	TArray<FAuraAttributeInfo> AttributeInfos;
	
	FAuraAttributeInfo FindAttributeInfoByTag(const FGameplayTag& InAttributeTag) const;
};
