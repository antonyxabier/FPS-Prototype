// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseCharacter.h"
#include "Actors/BaseRifle.h"


// Sets default values
ABaseCharacter::ABaseCharacter() : TeamID(0)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	GetMesh()->SetRelativeRotation(FRotator(0., -90., 0.));
	GetMesh()->SetRelativeLocation(FVector(0., 0., -90.));

	WeaponClass = ABaseRifle::StaticClass();

	ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>("ChildActorComponent");
	ChildActorComponent->SetupAttachment(GetMesh(), "PlaceWeaponHere");

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

}

ABaseRifle* ABaseCharacter::GetWeaponObject()
{
	return WeaponObject;
}

bool ABaseCharacter::CanPickupHealth_Implementation()
{
	return false;
}


void ABaseCharacter::HandleHurt(float ratio)
{
	CharacterAnimation->HitAnimation(ratio);
}

void ABaseCharacter::HandleDeathStart(float ratio)
{
	CharacterAnimation->DeathAnimation();
	this->SetActorEnableCollision(false);
	WeaponObject->OwnerDied();
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (ChildActorComponent) {
		// Set the child actor class
		if (WeaponClass)
		{
			ChildActorComponent->SetChildActorClass(WeaponClass);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ChildActorComponent is not set in %s"), *GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponClass is not set in %s"), *GetName());
	}

	WeaponObject = Cast<ABaseRifle>(ChildActorComponent->GetChildActor());
	CharacterAnimation = Cast<UCharacterAnimation>(GetMesh()->GetAnimInstance());

	if (WeaponObject && CharacterAnimation) {

		WeaponObject->CallOnRifleAttack.AddDynamic(CharacterAnimation, &UCharacterAnimation::FireAnimation);
		CharacterAnimation->OnReloadNow.AddDynamic(WeaponObject, &ABaseRifle::ReloadAmmo);
		CharacterAnimation->OnActionEnded.AddDynamic(WeaponObject, &ABaseRifle::ActionStopped);
		WeaponObject->OnReloadStart.AddDynamic(CharacterAnimation, &UCharacterAnimation::ReloadAnimation);
	}
	HealthComponent->OnHurt.AddDynamic(this, &ABaseCharacter::HandleHurt);
	HealthComponent->OnDeath.AddDynamic(this, &ABaseCharacter::HandleDeathStart);

	AController* contrlr = GetController();
	if (contrlr)
	{
		IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(contrlr);
		if (TeamAgent)
		{
			TeamAgent->SetGenericTeamId(TeamID);
		}
	}
}

void ABaseCharacter::OnFirePressed()
{
	// Ensure the CharacterAnimation is properly casted
	CharacterAnimation = Cast<UCharacterAnimation>(GetMesh()->GetAnimInstance());
	if (CharacterAnimation)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character Animation is Valid"));
		// Set DebugFire flag to true, this triggers the FireAnimation
		CharacterAnimation->FireAnimation_Implementation();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Character Animation is not Valid"));
	}

	// Handle weapon firing
	WeaponObject = Cast<ABaseRifle>(ChildActorComponent->GetChildActor());
	if (WeaponObject)
	{
		// Call the Attack method to spawn the projectile
		WeaponObject->Attack();

	}

}

void ABaseCharacter::OnReloadPressed()
{
	WeaponObject->RequestReload();
}


// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
//void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

//}

