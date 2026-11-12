// No Copyright.

#include "GameplayTags/AuraGameplayTags.h"

namespace AuraGameplayTags
{
	/** Input Tags */
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Move, "Input.Move", "None");
	
	/** Vital Attribute Tags */
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Vital_Health, "Attribute.Vital.Health", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Vital_MaxHealth, "Attribute.Vital.MaxHealth", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Vital_Mana, "Attribute.Vital.Mana", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Vital_MaxMana, "Attribute.Vital.MaxMana", "None");
	
	/** Message Tags */
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Potion_Health, "Message.Potion.Health", "None");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Potion_Mana, "Message.Potion.Mana", "None");
}
