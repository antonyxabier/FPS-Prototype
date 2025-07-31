// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseDamagePickup.h"
#include "BaseHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class END2503AC_API ABaseHealthPickup : public ABaseDamagePickup
{
	GENERATED_BODY()
	
public:
	ABaseHealthPickup();

protected:
	virtual void PostPickup() override;

	virtual bool CanPickup(AActor* otherActor) override;

};
