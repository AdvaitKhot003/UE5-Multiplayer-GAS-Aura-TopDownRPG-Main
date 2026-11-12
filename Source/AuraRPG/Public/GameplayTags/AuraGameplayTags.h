// No Copyright.

#pragma once

#include "NativeGameplayTags.h"

namespace AuraGameplayTags
{
	/** Input Tags */
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Move);
	
	/** Vital Attribute Tags */
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Health);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_MaxHealth);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Mana);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_MaxMana);
	
	/** Message Tags */
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Potion_Health);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Potion_Mana);
}
