// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpawner.h"
#include "ABGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"

// Sets default values
APlayerSpawner::APlayerSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerSpawner::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int APlayerSpawner::GetPlayerSize()
{
	UABGameInstance* MyGI = Cast<UABGameInstance>(GetGameInstance());
	nSizePlayer = MyGI->GetServerPlayer("Player");

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), OutActors);

	ServerPlayer = Cast<AMyPlayerController>(OutActors[0]);

	return nSizePlayer;
}

bool APlayerSpawner::CanSpawn()
{
	UABGameInstance* MyGI = Cast<UABGameInstance>(GetGameInstance());
	if (MyGI->GetIsServer("Player") == 0)
	{
		return false;
	}

	else
	{
		return true;
	}
}

void APlayerSpawner::GetPlayerVector(FVector getVec)
{
	ServerPlayer->ServerSetPlayerVector(getVec);
}