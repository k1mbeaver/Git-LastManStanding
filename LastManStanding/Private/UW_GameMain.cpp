// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_GameMain.h"
#include "UW_Chat.h"
#include "UW_Gameover.h"
#include "UW_Mission.h"
#include "UW_Death.h"
#include "UW_GameReady.h"

TSharedPtr<SWidget> UUW_GameMain::GetChatInputTextObject()
{
	return WB_Chat->GetChatInputTextObject();
}

void UUW_GameMain::AddChatMessage(const FString& Message)
{
	WB_Chat->AddChatMessage(Message);
}

void UUW_GameMain::SetPlayerMissionClear(int nMissionClear)
{
	WB_UserMission->SetPlayerMissionClear(nMissionClear);
}

void UUW_GameMain::SetWinnerName(const FString& WinnerName)
{
	WB_GameOver->SetWinnerName(WinnerName);
}

void UUW_GameMain::VisibleGameover()
{
	WB_GameOver->SetVisibility(ESlateVisibility::Visible);
}

void UUW_GameMain::VisibleDeath()
{
	WB_Death->SetVisibility(ESlateVisibility::Visible);
}

void UUW_GameMain::HiddenGameReady()
{
	WB_GameReady->SetVisibility(ESlateVisibility::Hidden);
}

void UUW_GameMain::InitServerUI(bool bServer)
{
	WB_GameReady->InitServerUI(bServer);
}