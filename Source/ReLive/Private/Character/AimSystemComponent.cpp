// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/AimSystemComponent.h"

// Sets default values for this component's properties
UAimSystemComponent::UAimSystemComponent(const FObjectInitializer& ObjectIn) : Super(ObjectIn) {}

bool UAimSystemComponent::Initialize() {
	Super::Initialize();
	if (Super::bInitialized) {
		// (1) - Create Root Panel
		class UPanelWidget* ROOT = Cast<UPanelWidget>(GetRootWidget());
		// (2) - Init The Root
		ROOT = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("ROOT"));
		if (ROOT != NULL) {
			// (3) - Create Text Widget
			CrosshairText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
			if (CrosshairText != NULL) {
				// (4) - Add UTextBlock To The Root
				ROOT->AddChild(CrosshairText);
				// (5) - Set color and text 
				const FSlateColor GREEN = FSlateColor(FLinearColor::Green);
				CrosshairText->SetColorAndOpacity(GREEN);
				CrosshairText->SetText(FText::FromString("^"));

				// (6) - SET Panel Slot (To Config Text Block Properties)
				UCanvasPanelSlot* panel = Cast<UCanvasPanelSlot>(CrosshairText->Slot);
				if (panel != NULL) {
					// ---- Set the Panel Layout in the Center of the Screen --
					panel->SetAnchors(FAnchors(0.5, 0.5));
					panel->SetAlignment(FVector2D(0.5f, 0.5f));
					panel->SetPosition(FVector2D(0, 0));
					panel->SetAutoSize(true);
					//@test 
					// Get The Pawn Owner 
					//class APawn *pawn = Cast<APawn>(GetOwningPlayerPawn());
					//if (pawn != NULL) {
						//@test 
					//    GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("CrosshairText OWNER = %s"), *pawn->GetName()));
					//}
				}
				// - Set Root
				WidgetTree->RootWidget = ROOT;
			}
		}
	}

	return (Super::bInitialized); // return true or false if it has been Initialized)
}


