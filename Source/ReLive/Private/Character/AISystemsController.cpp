// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AISystemsController.h"

AAISystemsController::AAISystemsController() {
	if (this != NULL) {
		BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
		//BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("[AAISystemsController] = Activated"));
	}
}





void AAISystemsController::OnPossess(class APawn* InPawn) {
	Super::OnPossess(InPawn);
	const FString Path = "/Game/Characters/Z1/AI/Z1BehaviorTree.Z1BehaviorTree";
	BehaviorTree = Cast<UBehaviorTree>(StaticLoadObject(UBehaviorTree::StaticClass(), nullptr, *Path));

	/* Hardcode Behavior Tree Path */
	if (BehaviorTree != NULL) {
		if (BehaviorComp) {
			BehaviorComp->StartTree(*BehaviorTree, EBTExecutionMode::Looped); // Looped type Behavior Tree
			//BehaviorComp->RestartLogic();//	Restarts currently running or previously ran brain logic.		
			//BehaviorComp->StartLogic();// Starts brain logic. If brain is already running, will not do anything.
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, TEXT("BehaviorTree = Loaded"));
		}		
	}

	//if (BehaviorTree != NULL) {
	//	if (BehaviorTree->BlackboardAsset != NULL) {
	//		BlackboardComp->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
	//		BehaviorComp->StartTree(*BehaviorTree);
	//		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("AI = POSSESSED"));
	//	}
	//}

}



void AAISystemsController::OnUnPossess() {
	Super::OnUnPossess();
	BehaviorComp->StopTree(); // Stop AI behavior running as we no longer have a pawn to control
	BehaviorComp->Cleanup(); //  AI logic won't be needed anymore, stop all activity and run cleanup
	BehaviorTree->ClearGarbage();
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("AI = UN-POSSESSED"));
}

