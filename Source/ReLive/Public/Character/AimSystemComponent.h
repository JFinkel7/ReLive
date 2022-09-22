// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"  // (REQUIRED)
#include "Components/PanelSlot.h"
#include "Components/PanelWidget.h" // (REQUIRED)
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h" 
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h" // (REQUIRED)
#include "AimSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RELIVE_API UAimSystemComponent : public UUserWidget {
	GENERATED_BODY()

	//! @brief: Text Crosshair for the player to aim 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* CrosshairText;

public:	
	// Sets default values for this component's properties
	UAimSystemComponent(const FObjectInitializer& ObjectIn);
	virtual bool Initialize() override;

private:
	bool IsAiming;
		
};
