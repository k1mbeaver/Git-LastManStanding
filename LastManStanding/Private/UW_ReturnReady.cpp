// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_ReturnReady.h"
#include "Components/Button.h"
#include "MyPlayerController.h"

void UUW_ReturnReady::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtBack = Cast<UButton>(GetWidgetFromName(TEXT("BtBack")));
}

void UUW_ReturnReady::NativeConstruct()
{
	Super::NativeConstruct();

	BtBack->OnClicked.AddDynamic(this, &UUW_ReturnReady::BackHandler);
}

void UUW_ReturnReady::BackHandler()
{
	AMyPlayerController* MyPC = Cast<AMyPlayerController>(GetOwningPlayer());
	if (MyPC)
	{
		MyPC->PlayerOut();
	}
}