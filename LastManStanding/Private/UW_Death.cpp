// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Death.h"
#include "Components/Button.h"
#include "MyPlayerController.h"

void UUW_Death::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtWatch = Cast<UButton>(GetWidgetFromName(TEXT("BtWatch")));
}

void UUW_Death::WatchCamera()
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());

	PlayerController->CameraChange();
}