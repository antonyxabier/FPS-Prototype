// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseCharacter.h"
#include "Actors/AIC_CodeAgentController.h"
#include "Utility/BI_CodeEnemyInterface.h"
#include "BaseAgent.generated.h"

/**
 * 
 */
UCLASS()
class END2503AC_API ABaseAgent : public ABaseCharacter, public IBI_CodeEnemyInterface
{
    GENERATED_BODY()

public:

    ABaseAgent();
    virtual void Attack() override;
    virtual void Reload() override;

    virtual FGenericTeamId GetGenericTeamId() const override { return TeamID; }

protected:

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void OnConstruction(const FTransform& Transform) override;
    virtual void PossessedBy(AController* NewController) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    FName TintName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    FLinearColor Color;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    class UCharacterAnimation* AnimationBP;

    virtual void HandleHurt(float ratio) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
    FName HealthRatio;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
    FName Ammo;


    UFUNCTION()
    void HandleActionFinished();

    UFUNCTION()
    void UpdateBlackboardHealth(float ratio);

    UFUNCTION()
    void UpdateBlackBoardAmmo(float Current, float Max);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
    FName ActionFinishedMessage;

    //AAIController* controller;

};
