// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_ReadyRoom.generated.h"

/**
 * 
 */
UCLASS()
class LASTMANSTANDING_API UUW_ReadyRoom : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(Meta = (BindWidget))
		class UButton* BtPlay;
	UPROPERTY(Meta = (BindWidget))
		class UButton* BtJoin;
	UPROPERTY(Meta = (BindWidget))
		class UButton* BtDecide;
	UPROPERTY(Meta = (BindWidget))
		class UButton* BtBack;
	UPROPERTY(Meta = (BindWidget))
		class UEditableTextBox* PlayerOne;
	UPROPERTY(Meta = (BindWidget))
		class UEditableTextBox* IPBox;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* IP;
	UPROPERTY(Meta = (BindWidget))
		class UComboBoxString* MeshCB;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextPlayer;
	UPROPERTY(Meta = (BindWidget))
		class UComboBoxString* PlayerCB;

public:

	//UFUNCTION()
		//void PlayHandler();
	//UFUNCTION()
		//void ReadyHandler();
	
	//virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

	void VisiblePlayButton();

	void VisibleJoinButton();

	void HiddenIPBox();

	void HiddenServerPlayer();

	FString GetTextBox();

	FString GetIp();

	UFUNCTION()
		void PlayHandler();
	UFUNCTION()
		void DecideHandler();
	UFUNCTION()
		void JoinHandler();
	UFUNCTION()
		void BackHandler();

	virtual void NativeConstruct() override;
};
