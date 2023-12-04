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

protected:
	virtual void NativeOnInitialized() override;

public:
	void GameStart();

	void InitServerUI(bool bServer);
};
