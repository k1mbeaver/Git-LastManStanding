// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ABGameInstance.generated.h"

/**
 * 
 */

struct FPlayerData;
class UDataTable;

UCLASS()
class LASTMANSTANDING_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UABGameInstance();
	FString GetUserName(FString Player);
	void SetUserName(FString Player, FString UserName);
	int GetIsServer(FString Player);
	void SetIsServer(FString Player, int ServerAndClient);
	USoundWave* GetSound(FString SoundName);
	USkeletalMesh* GetSkeletalMesh(FString MeshName);
	TSubclassOf<class UAnimInstance> GetAninInstance(FString MeshName);
	FString GetMapName(FString MapName);
	int GetMonsterSize(FString MapName);

private:
	UPROPERTY()
		UDataTable* FPlayerTable;

	UPROPERTY()
		UDataTable* FSoundTable;

	UPROPERTY()
		UDataTable* FMapTable;

	UPROPERTY()
		UDataTable* FMeshTable;
};
