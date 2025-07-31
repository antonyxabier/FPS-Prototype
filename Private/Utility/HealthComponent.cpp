// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent() : MaxHealth(5.0f), CurrentHealth(MaxHealth)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	//MaxHealth = 5.0f;
	//CurrentHealth = MaxHealth;

	// ...
}
// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner) {
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleDamage);

	}

	// ...

}
void UHealthComponent::HandleDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage == 0.0f)
	{
		return;
	}

	// Apply damage as a reduction
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);

	// Fire OnHurt event with the ratio
	if (Damage > 0.0f)
	{
		// Took damage
		OnHurt.Broadcast(CurrentHealth / MaxHealth);

		if (CurrentHealth <= 0.0f)
		{
			OnDeath.Broadcast(0.0f);
		}
	}
	else
	{
		// Healed
		OnHeal.Broadcast(CurrentHealth / MaxHealth);
	}
	// If health reaches 0, trigger death
	if (CurrentHealth <= 0.0f)
	{
		OnDeath.Broadcast(0.0);
	}
}





// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

