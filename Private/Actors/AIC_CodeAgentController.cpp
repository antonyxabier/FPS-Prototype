// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AIC_CodeAgentController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "../END2503AC.h"


AAIC_CodeAgentController::AAIC_CodeAgentController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));




	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 800.0f;
	SightConfig->LoseSightRadius = 1000.0f;
	SightConfig->PeripheralVisionAngleDegrees = 45.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 300.0f;

	PerceptionComponent->ConfigureSense(*SightConfig);

	//PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC_CodeAgentController::HandlePerception);

	PlayerKey = "Player";
}

void AAIC_CodeAgentController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	Super::SetGenericTeamId(NewTeamID);
	if (UAIPerceptionSystem* PerceptionSystem = UAIPerceptionSystem::GetCurrent(GetWorld()))
	{
		PerceptionSystem->UpdateListener(*GetPerceptionComponent());
	}
}


void AAIC_CodeAgentController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(InPawn))
	{
		//Degugging
		UE_LOG(LogTemp, Warning, TEXT("Setting Team ID: %d"), TeamAgent->GetGenericTeamId());


		SetGenericTeamId(TeamAgent->GetGenericTeamId());
	}
	RunBehaviorTree(BehaviorTree);

}

void AAIC_CodeAgentController::HandlePerception(AActor* Actor, FAIStimulus Stimulus)
{

	
		if (Stimulus.WasSuccessfullySensed()) {
			Blackboard->SetValueAsObject(PlayerKey, Actor);
		}
	

}
		
	

	

