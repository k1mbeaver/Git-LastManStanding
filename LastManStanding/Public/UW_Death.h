// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Death.generated.h"

/**
 * 
 */
UCLASS()
class LASTMANSTANDING_API UUW_Death : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Meta = (BindWidget))
		class UButton* BtWatch;
protected:
	virtual void NativeOnInitialized() override;

public:
	UFUNCTION(BlueprintCallable)
		void WatchCamera();
};
