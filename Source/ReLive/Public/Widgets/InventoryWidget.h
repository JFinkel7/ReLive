// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
//#include "Components/UniformGridPanel.h" // Required
//#include "Components/UniformGridSlot.h" // Required

#include "Components/HorizontalBox.h"

#include "InventoryWidget.generated.h"


UCLASS()
class RELIVE_API UInventoryWidget : public UUserWidget{
	GENERATED_BODY()

public:
	//! @brief: Initialize this component's
	virtual bool Initialize() override;

	//! @brief: Native Construct 
	virtual void NativeConstruct() override;

	//! @brief: To show change to blueprint properties in the editor 
	virtual void SynchronizeProperties() override;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Panel", meta = (BindWidget))
		class UHorizontalBox* JHorizontalBox = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Panel", meta = (BindWidget))
		class UTextBlock* JTextBlock = nullptr;

	
};
