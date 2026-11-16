// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

UCLASS()
class AURARPG_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAuraAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
#pragma region Primary Attributes
	/** Strength Attribute - Increases physical damage */
	UPROPERTY(ReplicatedUsing = OnRep_Strength, BlueprintReadOnly, Category = "Aura|Attributes|Primary")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Strength);
	
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	
	/** Intelligence Attribute - Increases magical damage */
	UPROPERTY(ReplicatedUsing = OnRep_Intelligence, BlueprintReadOnly, Category = "Aura|Attributes|Primary")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Intelligence);
	
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	
	/** Resilience Attribute - Increases Armor and Armor Penetration */
	UPROPERTY(ReplicatedUsing = OnRep_Resilience, BlueprintReadOnly, Category = "Aura|Attributes|Primary")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Resilience);
	
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	
	/** Vigor Attribute - Increases Health */
	UPROPERTY(ReplicatedUsing = OnRep_Vigor, BlueprintReadOnly, Category = "Aura|Attributes|Primary")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Vigor);
	
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
#pragma endregion
	
#pragma region Secondary Attributes
	/** Armor Attribute - Reduces damage taken, improves Block Chance */
	UPROPERTY(ReplicatedUsing = OnRep_Armor, BlueprintReadOnly, Category = "Aura|Attributes|Secondary")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Armor);
	
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	
	/** Armor Penetration Attribute - Ignores percentage of enemy Armor, increases Crit Hit Chance */
	UPROPERTY(ReplicatedUsing = OnRep_ArmorPenetration, BlueprintReadOnly, Category = "Aura|Attributes|Secondary")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, ArmorPenetration);
	
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	
	/** Block Chance Attribute - Chance to cut incoming damage in half */
	UPROPERTY(ReplicatedUsing = OnRep_BlockChance, BlueprintReadOnly, Category = "Aura|Attributes|Secondary")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, BlockChance);
	
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	
	/** Critical Hit Chance Attribute - Chance to double damage plus critical hit bonus */
	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitChance, BlueprintReadOnly, Category = "Aura|Attributes|Secondary")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, CriticalHitChance);
	
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
	
	/** Critical Hit Damage Attribute - Bonus damage added when a critical hit is scored */
	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitDamage, BlueprintReadOnly, Category = "Aura|Attributes|Secondary")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, CriticalHitDamage);
	
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
	
	/** Critical Hit Resistance Attribute - Reduces Critical Hit Chance of attacking enemies */
	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitResistance, BlueprintReadOnly, Category = "Aura|Attributes|Secondary")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, CriticalHitResistance);
	
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;
	
	/** Health Regeneration Attribute - Amount of Health regenerated every 1 second */
	UPROPERTY(ReplicatedUsing = OnRep_HealthRegeneration, BlueprintReadOnly, Category = "Aura|Attributes|Secondary")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, HealthRegeneration);
	
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	
	/** Mana Regeneration Attribute - Amount of Mana regenerated every 1 second */
	UPROPERTY(ReplicatedUsing = OnRep_ManaRegeneration, BlueprintReadOnly, Category = "Aura|Attributes|Secondary")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, ManaRegeneration);
	
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
	
	/** Max Health Attribute - Maximum amount of Health obtainable */
	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, BlueprintReadOnly, Category = "Aura|Attributes|Secondary")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, MaxHealth);
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	
	/** Max Mana Attribute - Maximum amount of Mana obtainable */
	UPROPERTY(ReplicatedUsing = OnRep_MaxMana, BlueprintReadOnly, Category = "Aura|Attributes|Secondary")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, MaxMana);
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
#pragma endregion
	
#pragma region Vital Attributes
	/** Health Attribute - current amount of life the character has */
	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, Category = "Aura|Attributes|Vital")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Health);
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	
	/** Mana Attribute - current amount of magical energy the character has to spend on abilities */
	UPROPERTY(ReplicatedUsing = OnRep_Mana, BlueprintReadOnly, Category = "Aura|Attributes|Vital")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Mana);
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
#pragma endregion
};
