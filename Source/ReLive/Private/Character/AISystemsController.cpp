// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AISystemsController.h"

AAISystemsController::AAISystemsController() {
	if (this != NULL) {
		BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	}
}





void AAISystemsController::OnPossess(class APawn* InPawn) {
	Super::OnPossess(InPawn);
	const FString Path = "/Game/Characters/Z1/AI/Z1BehaviorTree.Z1BehaviorTree";
	BehaviorTree = Cast<UBehaviorTree>(StaticLoadObject(UBehaviorTree::StaticClass(), nullptr, *Path));
	if (BehaviorTree != NULL) {
		if (BehaviorComp) {
			BehaviorComp->StartTree(*BehaviorTree, EBTExecutionMode::Looped); // Looped type Behavior Tree
			//@test message
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("AI = POSSESSED"));
		}		
	}
}



void AAISystemsController::OnUnPossess() {
	Super::OnUnPossess();
	BehaviorComp->StopTree(); // Stop AI behavior running as we no longer have a pawn to control
	BehaviorComp->Cleanup(); //  AI logic won't be needed anymore, stop all activity and run cleanup
	BehaviorTree->ClearGarbage();
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("AI = UN-POSSESSED"));
}

