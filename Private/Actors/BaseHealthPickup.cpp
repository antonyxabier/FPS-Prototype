// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseHealthPickup.h"
#include "Particles/ParticleSystemComponent.h"
#include "Utility/BI_CodePickupInterface.h"
#include "Components/BoxComponent.h"


ABaseHealthPickup::ABaseHealthPickup()
{
	baseDamage = -1.5f;

	particleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));

	particleSystem->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.7f));

	boxCollision->SetRelativeScale3D(FVector(1.5f, 1.5f, 2.0f));

}

void ABaseHealthPickup::PostPickup()
{
	ABasePickup::PostPickup();
}

bool ABaseHealthPickup::CanPickup(AActor* otherActor)
{
	if (otherActor && otherActor->Implements<UBI_CodePickupInterface>())
	{
		return IBI_CodePickupInterface::Execute_CanPickupHealth(otherActor);
	}

	return false;
}


