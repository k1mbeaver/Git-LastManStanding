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
	virtual void PostInitializeComponents() override; // ���⼭ ���ǵǴ��� �� �� ����
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
		int CurrentPlayer = 0;

	UPROPERTY(Replicated)
		int nPlayerNumber = 0;

private:
	void UpDown(float NewAxisValue);

	void LeftRight(float NewAxisValue);

	void LookUp(float NewAxisValue);

	void Turn(float NewAxisValue);

	void Jump();

	void StopJumping();

public:
	// RPC �Լ�
	void PlayerEnter();

	UFUNCTION(Server, Unreliable)
		void PlayerEnterToServer(AMyCharacter* PlayCharacter);

	UFUNCTION(Client, Unreliable)
		void PlayerEnterToClient(AMyCharacter* PlayCharacter);

	// RPC �Լ�
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

	void GameOver(const FString& WinnerName);

	UFUNCTION(Server, Unreliable)
		void GameoverToServer(const FString& WinnerName);

	UFUNCTION(Client, Unreliable)
		void GameoverToClient(const FString& WinnerName);

	void ReadyStart();

	UFUNCTION(Server, Unreliable)
		void ReadyStartToServer();

	UFUNCTION(Client, Unreliable)
		void ReadyStartToClient();

	void SendMessage(const FText& Text);

	UFUNCTION()
		void FocusChatInputText();

	UFUNCTION()
		void FocusGame();

	UFUNCTION(Server, Unreliable)
		void CtoS_SendMessage(const FString& Message);

	UFUNCTION(Client, Unreliable)
		void StoC_SendMessage(const FString& Message);

	// Ŭ���̾�Ʈ �Լ�

	void PlayerDeath();
	void EnterGameReady(bool bServer);
};
