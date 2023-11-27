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

private:
	void UpDown(float NewAxisValue);

	void LeftRight(float NewAxisValue);

	void LookUp(float NewAxisValue);

	void Turn(float NewAxisValue);

	void Jump();

	void StopJumping();

public:
	// 여기서 부터는 RPC 함수 사용해서 진행
	void PlayerEnter();

	UFUNCTION(Server, Unreliable)
		void PlayerEnterToServer(AMyCharacter* PlayCharacter);

	UFUNCTION(Client, Unreliable)
		void PlayerEnterToClient(AMyCharacter* PlayCharacter);

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
};
