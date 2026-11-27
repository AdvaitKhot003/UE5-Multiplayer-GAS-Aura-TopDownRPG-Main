// No Copyright.

#include "GameplayTags/AuraGameplayTags.h"

namespace AuraGameplayTags
{
	/** Input Tags */
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Move, "Input.Move", "None");
	
	/** Ability Input Tags */
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_RMB, "Input.RMB", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_LMB, "Input.LMB", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_1Key, "Input.1Key", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_2Key, "Input.2Key", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_3Key, "Input.3Key", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_4Key, "Input.4Key", "None");
	
	/** Primary Attribute Tags */
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Strength, "Attribute.Primary.Strength", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Intelligence, "Attribute.Primary.Intelligence", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Resilience, "Attribute.Primary.Resilience", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Vigor, "Attribute.Primary.Vigor", "None");
	
	/** Secondary Attribute Tags */
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_Armor, "Attribute.Secondary.Armor", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_ArmorPenetration, "Attribute.Secondary.ArmorPenetration", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_BlockChance, "Attribute.Secondary.BlockChance", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_CriticalHitChance, "Attribute.Secondary.CriticalHitChance", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_CriticalHitDamage, "Attribute.Secondary.CriticalHitDamage", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_CriticalHitResistance, "Attribute.Secondary.CriticalHitResistance", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_HealthRegeneration, "Attribute.Secondary.HealthRegeneration", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_ManaRegeneration, "Attribute.Secondary.ManaRegeneration", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_MaxHealth, "Attribute.Secondary.MaxHealth", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_MaxMana, "Attribute.Secondary.MaxMana", "None");
	
	/** Vital Attribute Tags */
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Vital_Health, "Attribute.Vital.Health", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Vital_Mana, "Attribute.Vital.Mana", "None");
	
	/** Event Tags */
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_Ability_FireBolt, "Event.Ability.FireBolt", "None");
	
	/** Message Tags */
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Potion_Health, "Message.Potion.Health", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Potion_Mana, "Message.Potion.Mana", "None");
}
