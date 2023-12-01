// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_ReadyRoom.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/ComboBoxString.h"
#include "ReadyRoom_PC.h"
#include "ABGameInstance.h"


void UUW_ReadyRoom::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtPlay = Cast<UButton>(GetWidgetFromName(TEXT("BtPlay")));
	BtDecide = Cast<UButton>(GetWidgetFromName(TEXT("BtDecide")));
	PlayerOne = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("PlayerOne")));
	IPBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("IPBox")));
	IP = Cast<UTextBlock>(GetWidgetFromName(TEXT("IP")));
	MeshCB = Cast<UComboBoxString>(GetWidgetFromName(TEXT("MeshCB")));
}


void UUW_ReadyRoom::NativeConstruct()
{
	Super::NativeConstruct();

	BtPlay->OnClicked.AddDynamic(this, &UUW_ReadyRoom::PlayHandler);
	BtDecide->OnClicked.AddDynamic(this, &UUW_ReadyRoom::DecideHandler);
	BtJoin->OnClicked.AddDynamic(this, &UUW_ReadyRoom::JoinHandler);

	UABGameInstance* MyGI = Cast<UABGameInstance>(GetGameInstance());

	TArray<FName> RowNames;
	RowNames = MyGI->GetMeshArray(); // Get the row names from the data table

	for (const FName& RowName : RowNames)
	{
		// Add each row name to the combo box
		MeshCB->AddOption(RowName.ToString());
	}

	MeshCB->SetSelectedOption("Man1");
}

void UUW_ReadyRoom::PlayHandler()
{
	AReadyRoom_PC* MyPC = Cast<AReadyRoom_PC>(GetOwningPlayer());
	UABGameInstance* MyGI = Cast<UABGameInstance>(GetGameInstance());
	if (MyPC)
	{
		MyGI->SetPlayerMesh("Player", MyGI->GetSkeletalMesh(MeshCB->GetSelectedOption()));
		MyGI->SetPlayerAnim("Player", MyGI->GetAninInstance(MeshCB->GetSelectedOption()));
		MyPC->Play();
	}
}

void UUW_ReadyRoom::DecideHandler()
{
	AReadyRoom_PC* MyPC = Cast<AReadyRoom_PC>(GetOwningPlayer());
	if (MyPC)
	{
		MyPC->Decide();
	}
}

void UUW_ReadyRoom::JoinHandler()
{
	AReadyRoom_PC* MyPC = Cast<AReadyRoom_PC>(GetOwningPlayer());
	UABGameInstance* MyGI = Cast<UABGameInstance>(GetGameInstance());
	if (MyPC)
	{
		MyGI->SetPlayerMesh("Player", MyGI->GetSkeletalMesh(MeshCB->GetSelectedOption()));
		MyGI->SetPlayerAnim("Player", MyGI->GetAninInstance(MeshCB->GetSelectedOption()));
		MyPC->Join();
	}
}

void UUW_ReadyRoom::VisiblePlayButton()
{
	BtPlay->SetVisibility(ESlateVisibility::Visible);
}

void UUW_ReadyRoom::VisibleJoinButton()
{
	BtJoin->SetVisibility(ESlateVisibility::Visible);
}

void UUW_ReadyRoom::HiddenIPBox()
{
	IP->SetVisibility(ESlateVisibility::Hidden);
	IPBox->SetVisibility(ESlateVisibility::Hidden);
}

FString UUW_ReadyRoom::GetTextBox()
{
	FString GetName = PlayerOne->GetText().ToString();
	return GetName;
}

FString UUW_ReadyRoom::GetIp()
{
	FString GetServerIp = IPBox->GetText().ToString();
	return GetServerIp;
}
/*
void UUW_ReadyRoom::VisibleJoinButton()
{
	BtJoin->SetVisibility(ESlateVisibility::Visible);
}
*/