// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_CodeAgentController.generated.h"


class UAISenseConfig_Sight;
class UBehaviorTree;
/**
 * 
 */
UCLASS()
class END2503AC_API AAIC_CodeAgentController : public AAIController
{
	GENERATED_BODY()

public:

	AAIC_CodeAgentController();

	//virtual void BeginPlay() override;

	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;

protected:

	
	//UFUNCTION(BlueprintCallable, Category = AI)
	virtual void OnPossess(APawn* InPawn) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName PlayerKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAISenseConfig_Sight* SightConfig;


private:
	UFUNCTION()
	void HandlePerception(AActor* Actor, FAIStimulus Stimulus);

	
	

};
