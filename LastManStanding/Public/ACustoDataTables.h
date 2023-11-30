// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ACustoDataTables.generated.h"

USTRUCT(BlueprintType)
struct FPlayerData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString NickName;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int IsServer;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
			FString MapName;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
			USkeletalMesh* PlayerMesh;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
			TSubclassOf<class UAnimInstance> MyAnimation;
};
UCLASS()
class LASTMANSTANDING_API AACustoDataTables : public AActor
{
	GENERATED_BODY()

};
