// No Copyright.

#include "Data/AuraAttributeInfoDataAsset.h"

FAuraAttributeInfo UAuraAttributeInfoDataAsset::FindAttributeInfoByTag(const FGameplayTag& InAttributeTag) const
{
	if (!InAttributeTag.IsValid()) return FAuraAttributeInfo();
	
	for (const FAuraAttributeInfo& AttributeInfo : AttributeInfos)
	{
		if (!AttributeInfo.IsValid() || !AttributeInfo.AttributeTag.MatchesTagExact(InAttributeTag)) continue;
		return AttributeInfo;
	}
	return FAuraAttributeInfo();
}
