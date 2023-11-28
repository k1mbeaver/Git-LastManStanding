// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "MyCharacter.generated.h"

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	ALIVE, // �������
	DEAD, // ����(����)
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

	UPROPERTY(VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;

	UPROPERTY()
		class AMyPlayerController* MyPC;

	UPROPERTY(Replicated)
		float fCurrentPawnSpeed;

	UPROPERTY(Replicated)
		float AttackRange;

	UPROPERTY(Replicated)
		float AttackRadius;

	UPROPERTY(Replicated)
		EPlayerState CurrentState;

	UPROPERTY(Replicated)
		float AttackPower;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		class UGameplayStatics* GameStatic;

	bool IsAttacking = false;

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

public:
	UFUNCTION(BlueprintCallable)
		void CharacterDead();

	UFUNCTION(NetMulticast, Reliable)
		void MultiDead(AMyCharacter* DeathCharacter); // ĳ���Ϳ� �÷��̾��ΰ�� �÷��̾� ��Ʈ�ѷ��� �޾ƿ´�.
};