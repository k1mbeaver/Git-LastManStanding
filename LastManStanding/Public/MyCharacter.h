// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "MyCharacter.generated.h"

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	ALIVE, // 살아있음
	DEAD, // 죽음(관전)
};

UCLASS()
class LASTMANSTANDING_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Replicated, Category = Animation)
		class UABAnimInstance* CharacterAnim;

	UPROPERTY(VisibleAnywhere, Replicated, Category = Mesh)
		class USkeletalMeshComponent* mySkeletalMesh;

	UPROPERTY(VisibleAnywhere, Replicated, Category = Mesh)
		class UAnimMontage* AttackMontage;

	UPROPERTY(VisibleAnywhere, Replicated, Category = Mesh)
		class UAnimMontage* DanceMontage;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;

	UPROPERTY()
		class AMyPlayerController* MyPC;

	UPROPERTY(Replicated)
		float fCurrentWalkSpeed = 200.0f;

	UPROPERTY(Replicated)
		float fCurrentRunSpeed = 400.0f;

	UPROPERTY(Replicated)
		float AttackRange;

	UPROPERTY(Replicated)
		float AttackRadius;

	UPROPERTY(VisibleAnywhere, Replicated)
		FVector StartLocation;

	UPROPERTY(Replicated)
		EPlayerState CurrentState;

	UPROPERTY(Replicated)
		float AttackPower;

	UPROPERTY(Replicated)
		FString PlayerName;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		class UGameplayStatics* GameStatic;

	bool IsAttacking = false;
	bool bCanMove = true;

public:	
	AMyCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamasgeCauser) override;

	void UpDown(float NewAxisValue);

	void LeftRight(float NewAxisValue);

	void LookUp(float NewAxisValue);

	void Turn(float NewAxisValue);

	void Run();

	void StopRun();

	virtual void Jump() override;

	virtual void StopJumping() override;

	void Attack();

	void AttackCheck();

	void Dancing();

	void DanceComplete();

	void StopDancing();

public:
	UFUNCTION(BlueprintCallable)
		void CharacterDead();

	UFUNCTION(NetMulticast, Reliable)
		void MultiDead(AMyCharacter* DeathCharacter); // 캐릭터와 플레이어인경우 플레이어 컨트롤러도 받아온다.
};
