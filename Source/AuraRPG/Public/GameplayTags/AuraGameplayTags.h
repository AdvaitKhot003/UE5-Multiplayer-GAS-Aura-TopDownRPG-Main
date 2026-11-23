// No Copyright.

#pragma once

#include "NativeGameplayTags.h"

namespace AuraGameplayTags
{
	/** Native Input Tags */
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Move);
	
	/** Ability Input Tags */
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_RMB);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_LMB);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_1Key);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_2Key);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_3Key);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_4Key);
	
	/** Primary Attribute Tags */
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Strength);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Intelligence);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Resilience);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Vigor);
	
	/** Secondary Attribute Tags */
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_Armor);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_ArmorPenetration);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_BlockChance);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_CriticalHitChance);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_CriticalHitDamage);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_CriticalHitResistance);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_HealthRegeneration);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_ManaRegeneration);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_MaxHealth);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_MaxMana);
	
	/** Vital Attribute Tags */
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Health);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Mana);
	
	/** Message Tags */
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Potion_Health);
	AURARPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Potion_Mana);
}
