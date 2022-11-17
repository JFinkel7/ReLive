// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryWidget.h"


bool UInventoryWidget::Initialize() {
	Super::Initialize();
	return true;
}


// - Set Up The Native Construct
void UInventoryWidget::NativeConstruct() {
	Super::NativeConstruct();

	//for (int i = 0; i < 0; i++) {
		if (JTextBlock) {
			JTextBlock->SetText(FText::FromString("Hello"));//JLabelText
		}
	//}
	

}


// When first creating a Blueprint subclass of this class,
// the widgets won't exist, so we must null check.
void UInventoryWidget::SynchronizeProperties() {
	Super::SynchronizeProperties();

}

