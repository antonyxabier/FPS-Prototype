// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CodeEnemyAttack.generated.h"

/**
 * 
 */
UCLASS()
class END2503AC_API UBTTask_CodeEnemyAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_CodeEnemyAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnMessageReceived(UBehaviorTreeComponent& OwnerComp, const FAIMessage& Message);

	UPROPERTY(EditDefaultsOnly)
	FName FinishedMessage;


		
	
};
