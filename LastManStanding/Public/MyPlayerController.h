// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LASTMANSTANDING_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

		AMyPlayerController();

public:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void PostInitializeComponents() override; // 여기서 빙의되는지 알 수 있음
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Pawn)
		class AMyCharacter* myCharacter;

	bool bChat = false;

public:
	UPROPERTY(Replicated)
		int DeathCount = 1;

	UPROPERTY(Replicated)
		int DefaultCount = 0;

	UPROPERTY(Replicated)
		int nPlayerNumber = 0;

	UPROPERTY(Replicated)
		bool bStart = false;

	UPROPERTY(Replicated)
		FVector StartLocation;

private:
	void UpDown(float NewAxisValue);

	void LeftRight(float NewAxisValue);

	void LookUp(float NewAxisValue);

	void Turn(float NewAxisValue);

	void Jump();

	void StopJumping();

public:
	// RPC 함수
	void PlayerEnter();

	UFUNCTION(Server, Unreliable)
		void PlayerEnterToServer(AMyCharacter* PlayCharacter);

	UFUNCTION(Client, Unreliable)
		void PlayerEnterToClient(AMyCharacter* PlayCharacter);

	// RPC 함수
	void PlayerOut();

	UFUNCTION(Server, Unreliable)
		void PlayerOutToServer();

	UFUNCTION(Client, Unreliable)
		void PlayerOutToClient();

	void Run();

	UFUNCTION(Server, Unreliable)
		void RunToServer(AMyCharacter* PlayCharacter);

	UFUNCTION(Client, Unreliable)
		void RunToClient(AMyCharacter* PlayCharacter);

	void StopRun();

	UFUNCTION(Server, Unreliable)
		void StopRunToServer(AMyCharacter* PlayCharacter);

	UFUNCTION(Client, Unreliable)
		void StopRunToClient(AMyCharacter* PlayCharacter);

	void Dancing();

	UFUNCTION(Server, Unreliable)
		void DancingToServer(AMyCharacter* PlayCharacter);

	UFUNCTION(Client, Unreliable)
		void DancingToClient(AMyCharacter* PlayCharacter);

	void StopDancing();

	UFUNCTION(Server, Unreliable)
		void StopDancingToServer(AMyCharacter* PlayCharacter);

	UFUNCTION(Client, Unreliable)
		void StopDancingToClient(AMyCharacter* PlayCharacter);

	void Attack();

	UFUNCTION(Server, Unreliable)
		void AttackToServer(AMyCharacter* PlayCharacter);

	UFUNCTION(Client, Unreliable)
		void AttackToClient(AMyCharacter* PlayCharacter);

	void CharacterDead();

	UFUNCTION(Server, Unreliable)
		void DeadToServer(AMyCharacter* PlayCharacter);

	UFUNCTION(Client, Unreliable)
		void DeadToClient(AMyCharacter* PlayCharacter);

	void GameOver();

	UFUNCTION(Server, Unreliable)
		void GameoverToServer(const FString& WinnerName);

	UFUNCTION(Client, Unreliable)
		void GameoverToClient(const FString& WinnerName);

	void ReadyStart();

	UFUNCTION(Server, Unreliable)
		void ReadyStartToServer();

	UFUNCTION(Client, Unreliable)
		void ReadyStartToClient(int ServerNumber, int PlayerCount);

	void SendMessage(const FText& Text);

	UFUNCTION()
		void FocusChatInputText();

	UFUNCTION()
		void FocusGame();

	UFUNCTION(Server, Unreliable)
		void CtoS_SendMessage(const FString& Message);

	UFUNCTION(Client, Unreliable)
		void StoC_SendMessage(const FString& Message);

	void StartCharacter(AMyCharacter* PlayCharacter, FVector CharacterLocation, USkeletalMesh* CharacterMesh, const FString& PlayerName);

	UFUNCTION(Server, Unreliable)
		void StartCharacterToServer(AMyCharacter* PlayCharacter, FVector CharacterLocation, USkeletalMesh* CharacterMesh, const FString& PlayerName);

	UFUNCTION(Client, Unreliable)
		void StartCharacterToClient(AMyCharacter* PlayCharacter, FVector CharacterLocation, USkeletalMesh* CharacterMesh, const FString& PlayerName);

	// 클라이언트 함수

	void PlayerDeath();
	void EnterGameReady(bool bServer);
};
