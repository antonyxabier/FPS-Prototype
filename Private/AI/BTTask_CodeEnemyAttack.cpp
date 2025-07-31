// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_CodeEnemyAttack.h"
#include "AIController.h"
#include "Utility/BI_CodeEnemyInterface.h"


UBTTask_CodeEnemyAttack::UBTTask_CodeEnemyAttack() 
{
	NodeName = "Enemy Attack";
	bNotifyTaskFinished = true;
	FinishedMessage = "ActionFinished";
}

EBTNodeResult::Type UBTTask_CodeEnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI Controller
	AAIController* controller = OwnerComp.GetAIOwner();
	if (!controller)
	{
		UE_LOG(LogTemp, Error, TEXT("BTTask_EnemyAttack: AI Controller is NULL"));
		return EBTNodeResult::Failed;
	}

	// Get Pawn controlled by AI
	APawn* ControlledPawn = controller->GetPawn();
	if (!ControlledPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("BTTask_EnemyAttack: Controlled Pawn is NULL"));
		return EBTNodeResult::Failed;
	}

	// Check if ControlledPawn implements the Enemy Interface
	IBI_CodeEnemyInterface* enemyInterface = Cast<IBI_CodeEnemyInterface>(ControlledPawn);
	if (enemyInterface)
	{
		// Call Attack function from interface
		enemyInterface->Attack();
		UE_LOG(LogTemp, Warning, TEXT("BTTask_EnemyAttack: Enemy Attacking!"));

		WaitForMessage(OwnerComp, FinishedMessage);

		// Finish task successfully
		return EBTNodeResult::InProgress;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BTTask_EnemyAttack: Pawn does not implement CodeEnemyInterface!"));
		return EBTNodeResult::Failed;
	}
}

