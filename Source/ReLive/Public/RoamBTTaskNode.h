// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController.h" // New 
#include "NavigationSystem.h" // New
#include "NavigationPath.h" // New

#include "RoamBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class RELIVE_API URoamBTTaskNode : public UBTTaskNode{
	GENERATED_BODY()

private: 
	//! @brief: This Task will be responsible to Move the AI to our chosen [Actor]
	//! @note: Make sure the composite node is [Selector]
	virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
