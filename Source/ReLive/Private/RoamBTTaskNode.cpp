// Fill out your copyright notice in the Description page of Project Settings.


#include "RoamBTTaskNode.h"

EBTNodeResult::Type URoamBTTaskNode::ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	class AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
	if (AIController != NULL) {
		const class APawn* AI = AIController->GetPawn();
		if (AI) {
			// (3) - Get Location
			const FVector ORIGIN = AI->GetActorLocation();
			// (4) - Get Current Navigation Mesh References
			const class UNavigationSystemV1* NAV = UNavigationSystemV1::GetCurrent(GetWorld());
			if (NAV != NULL) {
				// (5) - Set Nav Location Point
				struct FNavLocation randomPoint;
				// (6) - Get Random Nav Point
				if (NAV->GetRandomReachablePointInRadius(ORIGIN, 1500.0f, randomPoint)) {
					// (7) - Create FAI Move Request
					struct FAIMoveRequest request;
					request.SetCanStrafe(false); // Default (OFF)
					request.SetAllowPartialPath(true);// Default (ON) 
					request.SetUsePathfinding(true);// Default (ON)
					request.SetGoalLocation(randomPoint.Location);


					if (request.IsValid()) {//  Check Path Results
						switch (AIController->MoveTo(request)) {
							case(EPathFollowingRequestResult::AlreadyAtGoal):
							{
								//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Succeeded"));
								return EBTNodeResult::Succeeded;
							}

							case(EPathFollowingRequestResult::Failed):
							{
								//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed"));
								return EBTNodeResult::Failed;
							}
						}
					}


				}
			}
		}

	}

	return EBTNodeResult::Succeeded;
}

//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Roam Task = Executed"));