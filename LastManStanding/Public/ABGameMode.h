// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ABGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LASTMANSTANDING_API AABGameMode : public AGameModeBase
{
	GENERATED_BODY()

		AABGameMode();

public:
	virtual void PostLogin(APlayerController* NewPlayer) override; // 이 과정에서 플레이어 설정이 진행된다.
	
	int CurrentPlayer = 0;
	int DefaultPlayer = 0;
};
