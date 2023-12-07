// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "ABAICharacter.generated.h"

UCLASS()
class LASTMANSTANDING_API AABAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	TArray<FString> ArrMeshName = { "Man1", "Man2", "Man3", "Man4" };

	int RandomMesh(int min, int max); // 랜덤값 구하기
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamasgeCauser) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION()
		void CharacterDead();

	UFUNCTION(NetMulticast, Reliable)
		void MultiDead(AABAICharacter* DeathCharacter); // 캐릭터와 플레이어인경우 플레이어 컨트롤러도 받아온다.

	UPROPERTY(VisibleInstanceOnly, Replicated, Category = Animation)
		class UABAnimInstance* ABAnim;

	UPROPERTY()
		class AABAIController* ABAIController;

};
