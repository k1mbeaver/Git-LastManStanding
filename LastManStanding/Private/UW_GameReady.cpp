// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_GameReady.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MyPlayerController.h"
#include "ABGameInstance.h"

void UUW_GameReady::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtStart = Cast<UButton>(GetWidgetFromName(TEXT("BtStart")));
}

void UUW_GameReady::NativeConstruct()
{
	Super::NativeConstruct();

	UABGameInstance* MyGI = Cast<UABGameInstance>(GetGameInstance());

	if (MyGI->GetIsServer("Player") == 0)
	{
		InitServerUI(false);
	}

	else
	{
		InitServerUI(true);
	}
}

void UUW_GameReady::GameStart()
{
	// 여기서 서버가 게임을 시작하는 방향으로 진행
	AMyPlayerController* MyPC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (MyPC == nullptr) return;

	MyPC->ReadyStart();
}

void UUW_GameReady::InitServerUI(bool bServer)
{
	// 서버면 Start 버튼이 있고
	if (bServer)
	{
		BtStart->SetVisibility(ESlateVisibility::Visible);
	}

	// 클라이언트면 Start 버튼이 없음

	else
	{
		BtStart->SetVisibility(ESlateVisibility::Hidden);
	}
}