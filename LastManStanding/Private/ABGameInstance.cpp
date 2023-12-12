// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameInstance.h"
#include "ACustoDataTables.h"
#include "SoundDataTableClass.h"
#include "MapDataTableClass.h"
#include "MeshDataTableClass.h"
#include "AnimationDataTableClass.h"
#include "LocaitonDataTableClass.h"

UABGameInstance::UABGameInstance()
{
	FString PlayerDataPath = TEXT("DataTable'/Game/ThirdPersonCPP/Data/PlayerData.PlayerData'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABPLAYER(*PlayerDataPath);
	if (DT_ABPLAYER.Succeeded())
	{
		FPlayerTable = DT_ABPLAYER.Object;
	}

	
	FString MapDataPath = TEXT("DataTable'/Game/DataTable/MapDataTable.MapDataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MAP(*MapDataPath);
	if (DT_MAP.Succeeded())
	{
		FMapTable = DT_MAP.Object;
	}

	FString MeshDataPath = TEXT("DataTable'/Game/DataTable/MeshDataTable.MeshDataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MESH(*MeshDataPath);
	if (DT_MESH.Succeeded())
	{
		FMeshTable = DT_MESH.Object;
	}

	FString SoundDataPath = TEXT("DataTable'/Game/DataTable/SoundDataTable.SoundDataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SOUND(*SoundDataPath);
	if (DT_SOUND.Succeeded())
	{
		FSoundTable = DT_SOUND.Object;
	}

	FString AnimationDataPath = TEXT("DataTable'/Game/DataTable/AnimationDataTable.AnimationDataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ANIMATION(*AnimationDataPath);
	if (DT_ANIMATION.Succeeded())
	{
		FAnimationTable = DT_ANIMATION.Object;
	}

	FString LocationDataPath = TEXT("DataTable'/Game/DataTable/LocationDataTable.LocationDataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_LOCATION(*LocationDataPath);
	if (DT_LOCATION.Succeeded())
	{
		FLocationTable = DT_LOCATION.Object;
	}
}

FString UABGameInstance::GetUserName(FString Player)
{
	FPlayerData* PlayerData = FPlayerTable->FindRow<FPlayerData>(*Player, TEXT(""));
	FString PlayerNickName = PlayerData->NickName;
	return PlayerNickName;
}

void UABGameInstance::SetUserName(FString Player, FString UserName)
{
	FPlayerData* PlayerData = FPlayerTable->FindRow<FPlayerData>(*Player, TEXT(""));
	PlayerData->NickName = UserName;

	// 일단 여기까지 하고 대기방 구현후 다시 진행하자
}

USkeletalMesh* UABGameInstance::GetPlayerMesh(FString Player)
{
	FPlayerData* PlayerData = FPlayerTable->FindRow<FPlayerData>(*Player, TEXT(""));
	USkeletalMesh* PlayerMesh = PlayerData->PlayerMesh;
	return PlayerMesh;
}

void UABGameInstance::SetPlayerMesh(FString Player, USkeletalMesh* myMesh)
{
	FPlayerData* PlayerData = FPlayerTable->FindRow<FPlayerData>(*Player, TEXT(""));
	PlayerData->PlayerMesh = myMesh;
}

TSubclassOf<class UAnimInstance> UABGameInstance::GetPlayerAnim(FString Player)
{
	FPlayerData* PlayerData = FPlayerTable->FindRow<FPlayerData>(*Player, TEXT(""));
	TSubclassOf<class UAnimInstance> PlayerAnim = PlayerData->MyAnimation;
	return PlayerAnim;
}

void UABGameInstance::SetPlayerAnim(FString Player, TSubclassOf<class UAnimInstance> myAnim)
{
	FPlayerData* PlayerData = FPlayerTable->FindRow<FPlayerData>(*Player, TEXT(""));
	PlayerData->MyAnimation = myAnim;
}

int UABGameInstance::GetIsServer(FString Player)
{
	FPlayerData* PlayerData = FPlayerTable->FindRow<FPlayerData>(*Player, TEXT(""));
	int PlayerIsServer = PlayerData->IsServer;
	return PlayerIsServer;
}

void UABGameInstance::SetIsServer(FString Player, int ServerAndClient)
{
	FPlayerData* PlayerData = FPlayerTable->FindRow<FPlayerData>(*Player, TEXT(""));
	PlayerData->IsServer = ServerAndClient;

	// 일단 여기까지 하고 대기방 구현후 다시 진행하자
}

int UABGameInstance::GetServerPlayer(FString Player)
{
	FPlayerData* PlayerData = FPlayerTable->FindRow<FPlayerData>(*Player, TEXT(""));
	int nServerPlayer = PlayerData->ServerPlayer;
	return nServerPlayer;
}

int UABGameInstance::GetMaxServerPlayer(FString Player)
{
	FPlayerData* PlayerData = FPlayerTable->FindRow<FPlayerData>(*Player, TEXT(""));
	int nServerPlayer = PlayerData->MaxServerPlayer;
	return nServerPlayer;
}

void UABGameInstance::SetMaxServerPlayer(FString Player, int nServerPlayer)
{
	FPlayerData* PlayerData = FPlayerTable->FindRow<FPlayerData>(*Player, TEXT(""));
	PlayerData->MaxServerPlayer = nServerPlayer;
}

void UABGameInstance::SetServerPlayer(FString Player, int nServerPlayer)
{
	FPlayerData* PlayerData = FPlayerTable->FindRow<FPlayerData>(*Player, TEXT(""));
	PlayerData->ServerPlayer = nServerPlayer;
}

USoundWave* UABGameInstance::GetSound(FString SoundName)
{
	FSoundDataTable* SoundData = FSoundTable->FindRow<FSoundDataTable>(*SoundName, TEXT(""));
	USoundWave* mySound = SoundData->MySound;
	return mySound;
}

USkeletalMesh* UABGameInstance::GetSkeletalMesh(FString MeshName)
{
	FMeshDataTable* MeshData = FMeshTable->FindRow<FMeshDataTable>(*MeshName, TEXT(""));
	USkeletalMesh* mySkeletalMesh = MeshData->MySkeletalMesh;
	return mySkeletalMesh;
}

TSubclassOf<class UAnimInstance> UABGameInstance::GetAninInstance(FString MeshName)
{
	FMeshDataTable* MeshData = FMeshTable->FindRow<FMeshDataTable>(*MeshName, TEXT(""));
	TSubclassOf<class UAnimInstance> myAnim = MeshData->MyAnimation;
	return myAnim;
}


FString UABGameInstance::GetMapName(FString MapName)
{
	FMapDataTable* MapData = FMapTable->FindRow<FMapDataTable>(*MapName, TEXT(""));
	FString myMapName = MapData->MapName;
	return myMapName;
}

int UABGameInstance::GetMonsterSize(FString MapName)
{
	FMapDataTable* MapData = FMapTable->FindRow<FMapDataTable>(*MapName, TEXT(""));
	int MonsterSize = MapData->AISize;
	return MonsterSize;
}

UAnimMontage* UABGameInstance::GetMontage(FString AnimationName)
{
	FAnimationDataTable* AnimationData = FAnimationTable->FindRow<FAnimationDataTable>(*AnimationName, TEXT(""));
	UAnimMontage* myMontage = AnimationData->MyMontage;
	return myMontage;
}

TArray<FName> UABGameInstance::GetMeshArray()
{
	TArray<FName> myMeshData = FMeshTable->GetRowNames();
	return myMeshData;
}

FVector UABGameInstance::GetLocation(int myNumber)
{
	FString strNumber = FString::FromInt(myNumber);
	FLocationDataTable* LocationData = FLocationTable->FindRow<FLocationDataTable>(*strNumber, TEXT(""));
	FVector myLocation = LocationData->SpawnLocation;
	return myLocation;
}