// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Mission.h"
#include "Components/TextBlock.h"


void UUW_Mission::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Mission = Cast<UTextBlock>(GetWidgetFromName(TEXT("Mission")));
	DefaultMission = Cast<UTextBlock>(GetWidgetFromName(TEXT("DefaultMission")));
	PlayerMission = Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerMission")));
}
/*
void UUW_Mission::NativeConstruct()
{
	Super::NativeConstruct();

	Mission = Cast<UTextBlock>(GetWidgetFromName(TEXT("Mission")));
	DefaultMission = Cast<UTextBlock>(GetWidgetFromName(TEXT("DefaultMission")));
	PlayerMission = Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerMission")));
	KillingMission = Cast<UTextBlock>(GetWidgetFromName(TEXT("KillingMission")));
	PlayerKillingMission = Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerKillingMission")));
	DefaultKillingMission = Cast<UTextBlock>(GetWidgetFromName(TEXT("DefaultKillingMission")));
}
*/
void UUW_Mission::SetPlayerMissionClear(int nMissionClear)
{
	FString fsMissionClear = FString::FromInt(nMissionClear);
	FText ftMissionClear = FText::FromString(fsMissionClear);
	PlayerMission->SetText(ftMissionClear);
}