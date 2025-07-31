// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BasePickup.h"
#include "CodeMaxAmmoPickup.generated.h"

class ABaseRifle;

/**
 * 
 */
UCLASS()
class END2503AC_API ACodeMaxAmmoPickup : public ABasePickup
{
	GENERATED_BODY()

public:
	ACodeMaxAmmoPickup();

protected:
	virtual void HandlePickup(AActor* otherActor, FHitResult hitResult) override;

	virtual bool CanPickup(AActor* otherActor) override;

	virtual void PostPickup() override;

	UPROPERTY(EditDefaultsOnly)
	float MaxAmmo;
	ABaseRifle* WeaponObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Defaults)
	class UStaticMeshComponent* AmmoPickupMesh;
	
};
