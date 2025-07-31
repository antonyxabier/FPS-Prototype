// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BasePickup.h"
#include "BaseDamagePickup.generated.h"

class UParticlesystemComponent;

/**
 * 
 */
UCLASS()
class END2503AC_API ABaseDamagePickup : public ABasePickup
{
	GENERATED_BODY()

public:
	ABaseDamagePickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	UParticleSystemComponent* particleSystem;

protected:
	virtual void HandlePickup(AActor* otherActor, FHitResult hitResult) override;

	virtual void PostPickup() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float baseDamage;
	
};
