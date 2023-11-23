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

	UPROPERTY(VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;

	UPROPERTY()
		class AMyPlayerController* MyPC;

	UPROPERTY(Replicated)
		float fCurrentPawnSpeed;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		class UGameplayStatics* GameStatic;

public:	
	AMyCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	void UpDown(float NewAxisValue);

	void LeftRight(float NewAxisValue);

	void LookUp(float NewAxisValue);

	void Turn(float NewAxisValue);

	void Run();

	void StopRun();

	virtual void Jump() override;

	virtual void StopJumping() override;
};
