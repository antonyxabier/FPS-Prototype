// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseAgent.h"
#include "Actors/BaseRifle.h"
#include "BrainComponent.h"
#include "AIController.h"
#include "../END2503AC.h"
#include "BehaviorTree/BlackboardComponent.h"

ABaseAgent::ABaseAgent() : TintName("Tint"), ActionFinishedMessage("ActionFinished"), HealthRatio("HealthRatio"), Ammo("Ammo")
{
    PrimaryActorTick.bCanEverTick = true;

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    //controller = Cast<AAIController>(GetController());


}
void ABaseAgent::BeginPlay()
{
    Super::BeginPlay();

    //controller = Cast<AAIController>(GetController());

    if (!WeaponObject)
    {
        UE_LOG(LogTemp, Error, TEXT("WeaponObject is NULL for Agent: %s"), *GetName());
    }
    if (WeaponObject)
    {
        WeaponObject->OnActionStopped.AddDynamic(this, &ABaseAgent::HandleActionFinished);
    }
    UpdateBlackboardHealth(1.0f);
    WeaponObject->OnAmmoChanged.AddDynamic(this, &ABaseAgent::UpdateBlackBoardAmmo);
    WeaponObject->ReloadAmmo();
    CharacterAnimation->OnDeathEnded.AddDynamic(this, &ABaseAgent::K2_DestroyActor);
}



void ABaseAgent::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (WeaponObject)
    {
        //WeaponObject->Attack_Implementation();
    }
}

void ABaseAgent::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (GetMesh())
    {
        USkeletalMeshComponent* DynamicMaterial = GetMesh();
        if (DynamicMaterial)
        {
            DynamicMaterial->SetVectorParameterValueOnMaterials(TintName, FVector(Color));
        }
    }
}

void ABaseAgent::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    // At this point, NewController is guaranteed to be the controller possessing this pawn.
    // So GetController() will also return NewController.
    AAIController* AICon = Cast<AAIController>(NewController);
    if (AICon)
    {
        // Now you can safely get the blackboard component
        UBlackboardComponent* BBComp = AICon->GetBlackboardComponent();
        if (BBComp)
        {
            // Perform initial blackboard updates here if needed, e.g.
            // BBComp->SetValueAsFloat(HealthRatio, 1.0f);
            // BBComp->SetValueAsFloat(Ammo, WeaponObject->GetCurrentAmmo()); // Assuming WeaponObject is valid
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("BlackboardComponent is NULL for agent %s after possession!"), *GetName());
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Agent %s was possessed by a non-AIController!"), *GetName());
    }
}



void ABaseAgent::HandleHurt(float ratio)
{
    Super::HandleHurt(ratio);
    UpdateBlackboardHealth(ratio);
}

void ABaseAgent::HandleActionFinished()
{

    FAIMessage msg;
    msg.MessageName = ActionFinishedMessage;
    msg.Sender = this;
    msg.Status = FAIMessage::Success;
    FAIMessage::Send(this, msg);

   
    
   
}

void ABaseAgent::UpdateBlackboardHealth(float ratio)
{
    AAIController* AICon = Cast<AAIController>(GetController());
    if (AICon)
    {
        UBlackboardComponent* BBComp = AICon->GetBlackboardComponent();
        if (BBComp)
        {
            BBComp->SetValueAsFloat(HealthRatio, ratio);
        }
    }
    else
    {
        UE_LOG(Game, Error, TEXT("AICon is nullptr in UpdateBLackboardHealth"));
    }
}

void ABaseAgent::UpdateBlackBoardAmmo(float Current, float Max)
{
    AAIController* AICon = Cast<AAIController>(GetController());
    if (AICon)
    {
        UBlackboardComponent* BBComp = AICon->GetBlackboardComponent();
        if (BBComp)
        {
            BBComp->SetValueAsFloat(Ammo, Current);
        }
    }
    else
    {
        UE_LOG(Game, Error, TEXT("AICon is nullptr in UpdateBLackboardAmmo"));
    }

}
void ABaseAgent::Attack()
{
    UE_LOG(LogTemp, Log, TEXT("Base Agent is attacking"));
    if (WeaponObject) {
        WeaponObject->Attack();
    }
    else
    {
        UE_LOG(Game, Error, TEXT("WeaponObject is nullptr in Attack"));
    }
}

void ABaseAgent::Reload()
{
    if (WeaponObject) {
        WeaponObject->RequestReload();
    }
    else
    {
        UE_LOG(Game, Error, TEXT("WeaponObject is nullptr in Reload"));
    }
}

