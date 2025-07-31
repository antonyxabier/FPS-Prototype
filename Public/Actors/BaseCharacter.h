// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Both/CharacterAnimation.h"
#include "../Utility/HealthComponent.h"
#include "Utility/BI_CodePickupInterface.h"
#include "GenericTeamAgentInterface.h"
#include "BaseCharacter.generated.h"



UCLASS(Abstract)
class END2503AC_API ABaseCharacter : public ACharacter, public IBI_CodePickupInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UFUNCTION()
	ABaseRifle* GetWeaponObject();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team", meta = (AllowPrivateAccess = "true"))
	FGenericTeamId TeamID;


protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<AActor> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* ChildActorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class ABaseRifle* WeaponObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UCharacterAnimation* CharacterAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	UHealthComponent* HealthComponent;

	UFUNCTION(BlueprintCallable)
	virtual void HandleHurt(float ratio);
	UFUNCTION(BlueprintCallable)
	virtual void HandleDeathStart(float ratio);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	void OnFirePressed();
	void OnReloadPressed();

	virtual bool CanPickupHealth_Implementation() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> baseCharacterMesh;

};
