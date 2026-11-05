// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectActor.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class AURARPG_API AEffectActor : public AActor
{
	GENERATED_BODY()
	
public:
	AEffectActor();
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Aura|Effect")
	TObjectPtr<USphereComponent> EffectCollision;
	
	UPROPERTY(VisibleAnywhere, Category = "Aura|Effect")
	TObjectPtr<UStaticMeshComponent> EffectMesh;
};
