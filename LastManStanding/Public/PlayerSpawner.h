// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerSpawner.generated.h"

UCLASS()
class LASTMANSTANDING_API APlayerSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int nSizePlayer = 0;

	AMyPlayerController* ServerPlayer;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		int GetPlayerSize();

	UFUNCTION(BlueprintCallable)
		bool CanSpawn();

	UFUNCTION(BlueprintCallable)
		void GetPlayerVector(FVector getVec);

};
