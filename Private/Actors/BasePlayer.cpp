// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Actors/BaseRifle.h"
#include <Kismet/KismetMathLibrary.h>
#include "Utility/HealthComponent.h"
#include "Both/CharacterAnimation.h"

ABasePlayer::ABasePlayer()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComp->SetRelativeLocation(FVector(0., 80., 90.));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->TargetArmLength = 205.f;
	SpringArmComp->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArmComp);


}


void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	// Get Player Controller
	PlayerController = Cast<APlayerController>(GetController());

	// Ensure PlayerController exists
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("We Need A Player Controller to spawn the HUD"));
		return;
	}
	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("We Need A Health Component to spawn the HUD"));
	}

	// Create and add HUD to viewport
	if (HUDClass)
	{
		HUDWidget = CreateWidget(PlayerController, HUDClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
		if (HUDWidget)
		{
			UPlayerHUD* PlayerHUD = Cast<UPlayerHUD>(HUDWidget);
			if (PlayerHUD)
			{
				HealthComponent->OnHurt.AddDynamic(PlayerHUD, &UPlayerHUD::SetHealth);
				HealthComponent->OnDeath.AddDynamic(PlayerHUD, &UPlayerHUD::SetHealth);
				WeaponObject->OnAmmoChanged.AddDynamic(PlayerHUD, &UPlayerHUD::SetAmmo);
				WeaponObject->ReloadAmmo();
				HealthComponent->OnHeal.AddDynamic(PlayerHUD, &UPlayerHUD::SetHealth);
				CharacterAnimation->OnDeathEnded.AddDynamic(this, &ABasePlayer::PlayerLost);
			}

			if (HUDClass)
			{
				UE_LOG(LogTemp, Warning, TEXT("HUDClass is valid: %s"), *HUDClass->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("HUDClass is NULL at runtime!"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HUDClass is NULL at runtime!"));
	}
}



bool ABasePlayer::CanPickupHealth_Implementation()
{
	return true;
}

bool ABasePlayer::CanPickupAmmo_Implementation()
{
	return true;
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("TurnRight", this, &ABasePlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABasePlayer::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::InputAxisMoveForward);
	PlayerInputComponent->BindAxis("Strafe", this, &ABasePlayer::InputAxisStrafe);

	PlayerInputComponent->BindAction("AttackInput", IE_Pressed, this, &ABasePlayer::OnFirePressed);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ABasePlayer::OnReloadPressed);


}
void ABasePlayer::HandleHurt(float ratio)
{
	Super::HandleHurt(ratio);
	UPlayerHUD* PlayerHUD = Cast<UPlayerHUD>(HUDWidget);
	PlayerHUD->SetHealth(ratio);

}

void ABasePlayer::HandleDeathStart(float ratio)
{
	Super::HandleDeathStart(ratio);
	UPlayerHUD* PlayerHUD = Cast<UPlayerHUD>(HUDWidget);
	PlayerHUD->SetHealth(ratio);
	DisableInput(PlayerController);

}

void ABasePlayer::InputAxisMoveForward(float AxisValue)
{
	FRotator Break = GetControlRotation();
	FRotator Make(0., Break.Yaw, 0.);
	FVector WorldDirection = Make.Vector();

	// Move the actor forward
	AddMovementInput(WorldDirection, AxisValue);
}

void ABasePlayer::InputAxisStrafe(float AxisValue)
{
	FRotator Break = GetControlRotation();
	FRotator Make(0., Break.Yaw + 90, 0.);
	FVector WorldDirection = Make.Vector();

	// Strafe the actor 
	AddMovementInput(WorldDirection, AxisValue);

}

void ABasePlayer::PlayerLost()
{
	OnPlayerLost.Broadcast();

	// Always null-check pointers before dereferencing them!
	if (PlayerController) // Check if PlayerController is still valid
	{
		PlayerController->bShowMouseCursor = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ABasePlayer::PlayerLost - PlayerController is null when trying to show mouse cursor!"));
	}

	if (HUDWidget) // Check if HUDWidget is still valid
	{
		HUDWidget->RemoveFromParent();
		// It's safe to nullify AFTER you've used it and removed it from the hierarchy
		HUDWidget = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ABasePlayer::PlayerLost - HUDWidget is null when trying to remove from parent!"));
	}
}

void ABasePlayer::PlayerWin()
{
	DisableInput(PlayerController);
	HUDWidget->RemoveFromParent();
	HUDWidget = nullptr;
}

