// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_ReturnReady.generated.h"

/**
 * 
 */
UCLASS()
class LASTMANSTANDING_API UUW_ReturnReady : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Meta = (BindWidget))
		class UButton* BtBack;
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
public:
	UFUNCTION()
		void BackHandler();
};
