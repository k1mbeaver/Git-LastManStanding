// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadyRoom_PC.h"
#include "UW_ReadyRoomMain.h"
#include "ReadyRoomMain_HUD.h"
#include "ABGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AReadyRoom_PC::AReadyRoom_PC()
{

}

void AReadyRoom_PC::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);
	SetInputMode(FInputModeUIOnly());
}

void AReadyRoom_PC::VisiblePlay()
{
	AReadyRoomMain_HUD* HUD = GetHUD<AReadyRoomMain_HUD>();
	if (HUD == nullptr) return;

	HUD->VisiblePlayButton();
}

void AReadyRoom_PC::Play()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Demonstration", true, ((FString)("Listen")));
}

void AReadyRoom_PC::Decide()
{
	AReadyRoomMain_HUD* HUD = GetHUD<AReadyRoomMain_HUD>();
	UABGameInstance* MyGI = GetGameInstance<UABGameInstance>();

	if (HUD == nullptr) return;

	FString PlayerNickName = HUD->GetTextBox();

	MyGI->SetUserName("Player", PlayerNickName);
}

void AReadyRoom_PC::Join()
{
	AReadyRoomMain_HUD* HUD = GetHUD<AReadyRoomMain_HUD>();
	UABGameInstance* MyGI = GetGameInstance<UABGameInstance>();

	if (HUD == nullptr) return;

	FString GetServerIp = HUD->GetIp();

	UGameplayStatics::OpenLevel(GetWorld(), FName(GetServerIp));
}

void AReadyRoom_PC::Back()
{
	UABGameInstance* MyGI = GetGameInstance<UABGameInstance>();

	UGameplayStatics::OpenLevel(GetWorld(), FName("Title"));
}