// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_CodeEnemyReload.h"
#include "AIController.h"
#include "Utility/BI_CodeEnemyInterface.h"

EBTNodeResult::Type UBTTask_CodeEnemyReload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI Controller
	AAIController* controller = OwnerComp.GetAIOwner();
	if (!controller)
	{
		UE_LOG(LogTemp, Error, TEXT("Code_EnemyReload: AI Controller is NULL"));
		return EBTNodeResult::Failed;
	}

	// Get Pawn controlled by AI
	APawn* ControlledPawn = controller->GetPawn();
	if (!ControlledPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("Code_EnemyReload: Controlled Pawn is NULL"));
		return EBTNodeResult::Failed;
	}

	// Check if ControlledPawn implements the Enemy Interface
	IBI_CodeEnemyInterface* enemyInterface = Cast<IBI_CodeEnemyInterface>(ControlledPawn);
	if (enemyInterface)
	{
		// Call Reload function from enemy interface
		enemyInterface->Reload();
		UE_LOG(LogTemp, Warning, TEXT("Code_EnemyReload: Enemy Reloading!"));

		UBTTaskNode::WaitForMessage(OwnerComp, FinishedMessage);

		// Finish task successfully
		return EBTNodeResult::InProgress;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Code_EnemyReload: Pawn does not implement CodeEnemyInterface!"));
		return EBTNodeResult::Failed;
	}
}
