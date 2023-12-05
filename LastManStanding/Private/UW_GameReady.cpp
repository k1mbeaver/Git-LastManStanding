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
	// ���⼭ ������ ������ �����ϴ� �������� ����
	AMyPlayerController* MyPC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (MyPC == nullptr) return;

	MyPC->ReadyStart();
}

void UUW_GameReady::InitServerUI(bool bServer)
{
	// ������ Start ��ư�� �ְ�
	if (bServer)
	{
		BtStart->SetVisibility(ESlateVisibility::Visible);
	}

	// Ŭ���̾�Ʈ�� Start ��ư�� ����

	else
	{
		BtStart->SetVisibility(ESlateVisibility::Hidden);
	}
}