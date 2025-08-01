// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class UBoxComponent;

UCLASS(abstract)
class END2503AC_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	UBoxComponent* boxCollision;

	UFUNCTION(BlueprintCallable)
	virtual void HandlePickup(AActor* otherActor, FHitResult hitResult);

	UFUNCTION(BlueprintCallable)
	virtual void PostPickup();

	UFUNCTION(BlueprintPure)
	virtual bool CanPickup(AActor* otherActor);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void BoundOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

};
