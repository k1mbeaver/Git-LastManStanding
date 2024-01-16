// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_WatchMode.h"
#include "Components/Button.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UUW_WatchMode::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtQuit = Cast<UButton>(GetWidgetFromName(TEXT("BtQuit")));
}

void UUW_WatchMode::QuitTitle()
{
	AMyPlayerController* MyPC = Cast<AMyPlayerController>(GetOwningPlayer());
	if (MyPC)
	{
		MyPC->PlayerOut();
	}

	UGameplayStatics::OpenLevel(GetWorld(), FName("Title"));
}
