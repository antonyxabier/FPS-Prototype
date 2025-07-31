// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

// Delegate for health events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHurt, float, CurrentHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, float, CurrentHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeal, float, Ratio);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class END2503AC_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	
	UFUNCTION(BlueprintCallable)
	void HandleDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHurt OnHurt;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeath OnDeath;

	UPROPERTY()
	float MaxHealth;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHeal OnHeal;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	float CurrentHealth;
	
	
		
};
