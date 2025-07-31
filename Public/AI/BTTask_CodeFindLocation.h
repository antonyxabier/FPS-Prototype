// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CodeFindLocation.generated.h"

/**
 * 
 */
UCLASS()
class END2503AC_API UBTTask_CodeFindLocation : public UBTTaskNode
{
	GENERATED_BODY()
public:

	UBTTask_CodeFindLocation();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

private:
	UPROPERTY(EditDefaultsOnly)
	float Radius;

	UPROPERTY(EditDefaultsOnly)
	FName LocationName;
	
};
