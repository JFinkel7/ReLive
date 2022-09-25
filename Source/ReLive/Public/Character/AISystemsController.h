// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"  
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h" 
#include "AISystemsController.generated.h"

/**
 *
 */
UCLASS()
class RELIVE_API AAISystemsController : public AAIController {
	GENERATED_BODY()

	//! @brief: The Brainstem
	//! @note:  The Behavior Tree asset that was created and used to execute branches task nodes containing the logic.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* BehaviorTree;

	//! @brief: Memory Logic Making
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* BehaviorComp;

public: 
	//! @brief: AI Systems Controller properties
	AAISystemsController();


private:
	//! @brief: Called whenever the controller possesses a character bot
	virtual void OnPossess(class APawn* InPawn) override;

	//! @brief: Called whenever the controller removes possession of our character
	virtual void OnUnPossess() override;

};
