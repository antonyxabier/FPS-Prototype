// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePickup.h"
#include "Components/BoxComponent.h"

// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	boxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::BoundOverlap);

	SetRootComponent(boxCollision);


}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePickup::HandlePickup(AActor* otherActor, FHitResult hitResult)
{
}

void ABasePickup::PostPickup()
{
	Destroy();
}

bool ABasePickup::CanPickup(AActor* otherActor)
{
	return true;
}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePickup::BoundOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this) return;

	if (CanPickup(OtherActor))
	{
		HandlePickup(OtherActor, SweepResult);
		PostPickup();
	}
}

