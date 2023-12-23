// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawner.h"
#include "ABGameInstance.h"

// Sets default values
AAISpawner::AAISpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAISpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAISpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AAISpawner::GetMonsterSize()
{
	UABGameInstance* MyGI = Cast<UABGameInstance>(GetGameInstance());
	nSizeMonster = MyGI->GetServerAISize("Default");

	return nSizeMonster;
}

bool AAISpawner::CanSpawn()
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

void AAISpawner::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(AMyCharacter, bCanRun);
}

