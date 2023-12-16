// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_GameReady.generated.h"

/**
 * 
 */
UCLASS()
class LASTMANSTANDING_API UUW_GameReady : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Meta = (BindWidget))
		class UButton* BtStart;

	UPROPERTY(Meta = (BindWidget))
		class UButton* BtBack;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextCurrentPlayer;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextDefaultPlayer;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextSlash;

protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void GameStart();

	UFUNCTION(BlueprintCallable)
		void BackHandler();

	void InitServerUI(bool bServer);

	void VisiblePlayer(bool bServer);

	void SetDefaultPlayer(int nDefaultPlayer);

	void SetCurrentPlayer(int nCurrentPlayer);

	void StartEnabled(bool bCanStart);
};
