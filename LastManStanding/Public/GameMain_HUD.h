// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameMain_HUD.generated.h"

/**
 * 
 */
UCLASS()
class LASTMANSTANDING_API AGameMain_HUD : public AHUD
{
	GENERATED_BODY()

public:
	AGameMain_HUD();
	virtual void BeginPlay() override;

public:
	TSharedPtr<class SWidget> GetChatInputTextObject();
	void AddChatMessage(const FString& Message);
	void SetPlayerMissionClear(int nMissionClear);
	void SetWinnerName(const FString& WinnerName);
	void VisibleGameover();
	void VisibleDeath(bool bVisible);
	void HiddenGameReady();
	void InitServerUI(bool bServer);
	void SetCurrentPlayer(int nCurrentPlayer);
	void SetDefaultPlayer(int nDefaultPlayer);
	void StartEnabled(bool bCanStart);
	void SetReturnReady(bool bReturn);
	void SetWatchMode();
private:
	TSubclassOf<class UUW_GameMain> MainUIClass;
	class UUW_GameMain* MainUIObject;

private:
	bool CheckUIObject();
	bool CreateUIObject();
};
