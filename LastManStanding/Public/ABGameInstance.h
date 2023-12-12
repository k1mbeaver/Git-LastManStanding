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
	int GetServerPlayer(FString Player);
	void SetServerPlayer(FString Player, int nServerPlayer);
	int GetMaxServerPlayer(FString Player);
	void SetMaxServerPlayer(FString Player, int nServerPlayer);
	int GetIsServer(FString Player);
	void SetIsServer(FString Player, int ServerAndClient);
	void SetPlayerMesh(FString Player, USkeletalMesh* myMesh);
	void SetPlayerAnim(FString Player, TSubclassOf<class UAnimInstance> myAnim);
	TSubclassOf<class UAnimInstance> GetPlayerAnim(FString Player);
	USkeletalMesh* GetPlayerMesh(FString Player);
	USoundWave* GetSound(FString SoundName);
	USkeletalMesh* GetSkeletalMesh(FString MeshName);
	TSubclassOf<class UAnimInstance> GetAninInstance(FString MeshName);
	FString GetMapName(FString MapName);
	int GetMonsterSize(FString MapName);
	UAnimMontage* GetMontage(FString MontageName);
	TArray<FName> GetMeshArray();
	FVector GetLocation(int myNumber);

private:
	UPROPERTY()
		UDataTable* FPlayerTable;

	UPROPERTY()
		UDataTable* FSoundTable;

	UPROPERTY()
		UDataTable* FMapTable;

	UPROPERTY()
		UDataTable* FMeshTable;

	UPROPERTY()
		UDataTable* FAnimationTable;

	UPROPERTY()
		UDataTable* FLocationTable;
};
