// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseRifle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCallOnRifleAttack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCallOnActionStopped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCallOnAmmoChanged, float, Current, float, Max);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCallOnReloadStart);


UCLASS()
class END2503AC_API ABaseRifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseRifle();

	UFUNCTION(BlueprintCallable)
	void Attack();
	//virtual void Attack_Implementation();
	
	UFUNCTION(BlueprintPure, Category = Weapon)
	FVector GetSource();

	UFUNCTION(BlueprintCallable)
	void OwnerDied();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	float MaxAmmo;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ReloadAmmo();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void RequestReload();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ActionStopped();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void IncreaseMaxAmmo(float ammo = 50.f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Defaults)
	class USkeletalMeshComponent* baseRifleMesh;

	//Parent pawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	APawn* ParentPawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	FName WeaponSocketName;	

	FTimerHandle timer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	float ResetTime;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void UseAmmo();

	

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Create delegate
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Delegate)
	FCallOnRifleAttack CallOnRifleAttack;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Delegate)
	FCallOnActionStopped OnActionStopped;

	bool Alive = true;

	UPROPERTY(BlueprintAssignable, Category = Delagate)
	FCallOnAmmoChanged OnAmmoChanged;

	UPROPERTY(BlueprintAssignable, Category = Delagate)
	FCallOnReloadStart OnReloadStart;

private:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool CanShoot() const;
	bool ActionHappening;

	float CurrentAmmo;

	void HandleActionFinished();

};
