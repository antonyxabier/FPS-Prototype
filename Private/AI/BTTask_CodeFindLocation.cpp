// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_CodeFindLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"



UBTTask_CodeFindLocation::UBTTask_CodeFindLocation() : Radius(1000.f), LocationName("Location")
{
	NodeName = " Find Location";
}

EBTNodeResult::Type UBTTask_CodeFindLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* controller = OwnerComp.GetAIOwner();
	if (!controller) {
		UE_LOG(LogTemp, Error, TEXT("We need a Valid Controller"));
		return EBTNodeResult::Failed;
	}
	APawn* pawn = controller->GetPawn();
	if (!pawn) {
		UE_LOG(LogTemp, Error, TEXT("We need a Valid Pawn"));

		return EBTNodeResult::Failed;
	}
	UNavigationSystemV1* nav = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!nav) {
		UE_LOG(LogTemp, Error, TEXT("We need a Valid Navigation System"));
		return EBTNodeResult::Failed;
	}
	FVector origin = pawn->GetActorLocation();

	FVector randomLocation;
	FNavLocation navLocation;

	if (nav->GetRandomPointInNavigableRadius(origin, Radius, navLocation))
		randomLocation = navLocation;
	else {
		UE_LOG(LogTemp, Error, TEXT("Get Random Point In NavigableRadius FAILED"));
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* blackBoard = controller->GetBlackboardComponent();
	if (blackBoard)
		blackBoard->SetValueAsVector(LocationName, randomLocation);

	return EBTNodeResult::Succeeded;
}
