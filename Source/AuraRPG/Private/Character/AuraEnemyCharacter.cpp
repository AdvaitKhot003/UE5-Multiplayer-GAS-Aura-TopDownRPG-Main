// No Copyright.

#include "Character/AuraEnemyCharacter.h"
#include "AuraRPG/AuraRPG.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraEnemyCharacter::AAuraEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AuraAbilitySystemComp");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AuraAttributeSet");
}

void AAuraEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityCharacterInfo();
}

void AAuraEnemyCharacter::InitAbilityCharacterInfo()
{
	if (!AbilitySystemComponent) return;
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

UAbilitySystemComponent* AAuraEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AAuraEnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void AAuraEnemyCharacter::HighlightEnemy()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
	if (!WeaponMesh) return;
	WeaponMesh->SetRenderCustomDepth(true);
	WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemyCharacter::UnhighlightEnemy()
{
	GetMesh()->SetRenderCustomDepth(false);
	
	if (!WeaponMesh) return;
	WeaponMesh->SetRenderCustomDepth(false);
}
