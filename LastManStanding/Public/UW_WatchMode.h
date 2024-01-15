// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_WatchMode.generated.h"

/**
 * 
 */
UCLASS()
class LASTMANSTANDING_API UUW_WatchMode : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(Meta = (BindWidget))
		class UButton* BtQuit;
protected:
	virtual void NativeOnInitialized() override;

public:
	UFUNCTION(BlueprintCallable)
		void Quit();
};
