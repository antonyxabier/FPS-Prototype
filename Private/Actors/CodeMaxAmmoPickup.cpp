// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CodeMaxAmmoPickup.h"
#include "Components/BoxComponent.h"
#include "Actors/BasePlayer.h"
#include "Actors/BaseRifle.h"
#include "Components/StaticMeshComponent.h"

ACodeMaxAmmoPickup::ACodeMaxAmmoPickup() : MaxAmmo(5.0f)
{
	boxCollision->SetRelativeScale3D(FVector(1.6f, 1.6f, 0.5f));
	boxCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	AmmoPickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoPickupMesh"));
	AmmoPickupMesh->SetRelativeLocation(FVector(0.f, 0.f, -32.f));
	AmmoPickupMesh->SetRelativeScale3D(FVector(0.8f, 0.85f, 2.1f));
	AmmoPickupMesh->SetupAttachment(boxCollision);

}

void ACodeMaxAmmoPickup::HandlePickup(AActor* otherActor, FHitResult hitResult)
{
	Super::HandlePickup(otherActor, hitResult);

	ABasePlayer* player = Cast<ABasePlayer>(otherActor);
	if (player)
	{
		WeaponObject = Cast<ABaseRifle>(player->GetWeaponObject());
		if (WeaponObject)
		{
			WeaponObject->IncreaseMaxAmmo(MaxAmmo);
		}
	}

}

bool ACodeMaxAmmoPickup::CanPickup(AActor* otherActor)
{
	if (otherActor && otherActor->Implements<UBI_CodePickupInterface>())
	{
		return IBI_CodePickupInterface::Execute_CanPickupHealth(otherActor);
	}
	return false;
}

void ACodeMaxAmmoPickup::PostPickup()
{
	Super::PostPickup();
}
