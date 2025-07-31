// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/BP_CodeActionEnded.h"
#include "Actors/BaseCharacter.h"

void UBP_CodeActionEnded::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}

void UBP_CodeActionEnded::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (UCharacterAnimation* Anim = Cast<UCharacterAnimation>(MeshComp->GetAnimInstance())) {
		Anim->OnActionEnded.Broadcast();
	}
}
