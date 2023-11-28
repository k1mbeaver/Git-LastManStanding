// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Death.h"
#include "Components/Button.h"
#include "ABPlayerController.h"

void UUW_Death::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtWatch = Cast<UButton>(GetWidgetFromName(TEXT("BtWatch")));
}

