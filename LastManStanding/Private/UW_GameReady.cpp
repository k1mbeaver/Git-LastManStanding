// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_GameReady.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MyPlayerController.h"
#include "ABGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UUW_GameReady::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtStart = Cast<UButton>(GetWidgetFromName(TEXT("BtStart")));
	BtBack = Cast<UButton>(GetWidgetFromName(TEXT("BtBack")));
	TextCurrentPlayer = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextCurrentPlayer")));
	TextDefaultPlayer = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextDefaultPlayer")));
	TextSlash = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextSlash")));
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
		UABGameInstance* MyGI = Cast<UABGameInstance>(GetGameInstance());
		BtStart->SetVisibility(ESlateVisibility::Visible);
		VisiblePlayer(bServer);
		SetDefaultPlayer(MyGI->GetServerPlayer("Player"));
		SetCurrentPlayer(1);
	}

	// Ŭ���̾�Ʈ�� Start ��ư�� ����

	else
	{
		BtStart->SetVisibility(ESlateVisibility::Hidden);
		VisiblePlayer(bServer);
	}
}

void UUW_GameReady::VisiblePlayer(bool bServer)
{
	// ������ Start ��ư�� �ְ�
	if (bServer)
	{
		TextCurrentPlayer->SetVisibility(ESlateVisibility::Visible);
		TextDefaultPlayer->SetVisibility(ESlateVisibility::Visible);
		TextSlash->SetVisibility(ESlateVisibility::Visible);
	}

	// Ŭ���̾�Ʈ�� Start ��ư�� ����

	else
	{
		TextCurrentPlayer->SetVisibility(ESlateVisibility::Hidden);
		TextDefaultPlayer->SetVisibility(ESlateVisibility::Hidden);
		TextSlash->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UUW_GameReady::SetDefaultPlayer(int nDefaultPlayer)
{
	FString fsDefaultPlayer = FString::FromInt(nDefaultPlayer);
	FText ftDefaultPlayer = FText::FromString(fsDefaultPlayer);
	TextDefaultPlayer->SetText(ftDefaultPlayer);
}

void UUW_GameReady::SetCurrentPlayer(int nCurrentPlayer)
{
	FString fsCurrentPlayer = FString::FromInt(nCurrentPlayer);
	FText ftCurrentPlayer = FText::FromString(fsCurrentPlayer);
	TextCurrentPlayer->SetText(ftCurrentPlayer);
}

void UUW_GameReady::StartEnabled(bool bCanStart)
{
	if (bCanStart)
	{
		BtStart->SetIsEnabled(true);
	}

	else
	{
		BtStart->SetIsEnabled(false);
	}
}

void UUW_GameReady::BackHandler()
{
	AMyPlayerController* MyPC = Cast<AMyPlayerController>(GetOwningPlayer());
	if (MyPC)
	{
		MyPC->PlayerOut();
	}

	UGameplayStatics::OpenLevel(GetWorld(), FName("Title"));
}