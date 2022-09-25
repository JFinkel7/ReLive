// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NavigationPath.h" 
#include "NavigationSystem.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RoamBTTaskNode.generated.h"

UCLASS()
class RELIVE_API URoamBTTaskNode : public UBTTaskNode{
	GENERATED_BODY()

private: 
	//! @brief: Will move the AI to random locations within the Nav-Mesh
	//! @note: This task is added from the BehaviorTree
	virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
