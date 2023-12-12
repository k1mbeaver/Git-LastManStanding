// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameMode.h"
#include "ABCharacter.h"
#include "ABAIController.h"
#include "ABPlayerController.h"
#include "GameMain_HUD.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"

/*
1. 플레이어 컨트롤러의 생성, AI 컨트롤러의 생성
2. 플레이어 폰의 생성, AI 폰의 생성
3. 플레이어 컨트롤러가 플레이어 폰을 빙의, AI 컨트롤러가 AI 폰을 빙의
4. 게임의 시작
*/
AABGameMode::AABGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("Blueprint'/Game/BluePrint/BP_MyCharacter.BP_MyCharacter_C'"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	PlayerControllerClass = AMyPlayerController::StaticClass();
	HUDClass = AGameMain_HUD::StaticClass();

}

void AABGameMode::PostLogin(APlayerController* NewPlayer)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);

	AMyPlayerController* MyPC = Cast<AMyPlayerController>(NewPlayer);
	MyPC->PlayerEnter();

	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("PostLogin End"));

}