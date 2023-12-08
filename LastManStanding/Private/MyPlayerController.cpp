// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ABGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameMain_HUD.h"

AMyPlayerController::AMyPlayerController()
{

}

void AMyPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	myCharacter = Cast<AMyCharacter>(GetPawn());
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Success!"));
}

void AMyPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Possess!"));
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);
	SetInputMode(FInputModeUIOnly());

	// 나중에 여러 좌표를 설정해서 소환하게끔 구현
	StartLocation = FVector(1050.0f, -2920.0f, 142.0f);
}


void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStart)
	{
		if (DeathCount == DefaultCount)
		{
			if (myCharacter->CurrentState == EPlayerState::ALIVE)
			{
				bWinner = true;
			}
		}

		if (bWinner)
		{
			GameOver();
			bStart = false;
		}
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 채팅 함수
	InputComponent->BindAction(TEXT("Chat"), EInputEvent::IE_Pressed, this, &AMyPlayerController::FocusChatInputText);

	// 캐릭터 이동 함수
	InputComponent->BindAxis(TEXT("UpDown"), this, &AMyPlayerController::UpDown);
	InputComponent->BindAxis(TEXT("LeftRight"), this, &AMyPlayerController::LeftRight);
	InputComponent->BindAxis(TEXT("LookUp"), this, &AMyPlayerController::LookUp);
	InputComponent->BindAxis(TEXT("Turn"), this, &AMyPlayerController::Turn);

	//캐릭터 달리기
	InputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &AMyPlayerController::Run);
	InputComponent->BindAction(TEXT("Run"), IE_Released, this, &AMyPlayerController::StopRun);

	// 캐릭터 점프
	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMyPlayerController::Jump);
	InputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AMyPlayerController::StopJumping);

	// 캐릭터 공격
	InputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &AMyPlayerController::Attack);

	// 캐릭터 댄스
	InputComponent->BindAction(TEXT("Dance"), IE_Pressed, this, &AMyPlayerController::Dancing);
	InputComponent->BindAction(TEXT("Dance"), IE_Released, this, &AMyPlayerController::StopDancing);

}

void AMyPlayerController::UpDown(float NewAxisValue)
{
	if (!myCharacter)
	{
		return;
	}

	if (myCharacter->CurrentState == EPlayerState::ALIVE)
	{
		myCharacter->UpDown(NewAxisValue);
	}
}

void AMyPlayerController::LeftRight(float NewAxisValue)
{
	if (!myCharacter)
	{
		return;
	}

	if (myCharacter->CurrentState == EPlayerState::ALIVE)
	{
		myCharacter->LeftRight(NewAxisValue);
	}
}

void AMyPlayerController::LookUp(float NewAxisValue)
{
	if (!myCharacter)
	{
		return;
	}

	if (myCharacter->CurrentState == EPlayerState::ALIVE)
	{
		myCharacter->LookUp(NewAxisValue);
	}
}

void AMyPlayerController::Turn(float NewAxisValue)
{
	if (!myCharacter)
	{
		return;
	}

	if (myCharacter->CurrentState == EPlayerState::ALIVE)
	{
		myCharacter->Turn(NewAxisValue);
	}
}

void AMyPlayerController::Jump()
{
	if (!myCharacter)
	{
		return;
	}

	if (myCharacter->CurrentState == EPlayerState::ALIVE)
	{
		myCharacter->Jump();
	}
}

void AMyPlayerController::StopJumping()
{
	if (!myCharacter)
	{
		return;
	}

	if (myCharacter->CurrentState == EPlayerState::ALIVE)
	{
		myCharacter->StopJumping();
	}
}

void AMyPlayerController::PlayerEnter()
{
	if (myCharacter)
	{	
		PlayerEnterToServer(myCharacter);
	}
}

void AMyPlayerController::PlayerEnterToServer_Implementation(AMyCharacter* PlayCharacter)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	for (AActor* OutActor : OutActors)
	{
		AMyPlayerController* PC = Cast<AMyPlayerController>(OutActor);
		if (PC)
		{
			PC->PlayerEnterToClient(PlayCharacter);
		}
	}
}

void AMyPlayerController::PlayerEnterToClient_Implementation(AMyCharacter* PlayCharacter)
{
	if (PlayCharacter == NULL) // 캐릭터에 빙의되지 않은 경우에는 실행하지 않게하자.
	{
		return;
	}


}

void AMyPlayerController::PlayerOut()
{
	PlayerOutToServer();
}

void AMyPlayerController::PlayerOutToServer_Implementation()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	for (AActor* OutActor : OutActors)
	{
		AMyPlayerController* PC = Cast<AMyPlayerController>(OutActor);
		if (PC)
		{
			PC->PlayerOutToClient();
		}
	}
}

void AMyPlayerController::PlayerOutToClient_Implementation()
{
	//
}

void AMyPlayerController::Run()
{
	if (!myCharacter)
	{
		return;
	}

	if (myCharacter->CurrentState == EPlayerState::ALIVE)
	{
		RunToServer(myCharacter);
	}
}

void AMyPlayerController::RunToServer_Implementation(AMyCharacter* PlayCharacter)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	for (AActor* OutActor : OutActors)
	{
		AMyPlayerController* PC = Cast<AMyPlayerController>(OutActor);
		if (PC)
		{
			PlayCharacter->Run();
			PC->RunToClient(PlayCharacter);
		}
	}
}

void AMyPlayerController::RunToClient_Implementation(AMyCharacter* PlayCharacter)
{
	if (PlayCharacter == NULL) // 캐릭터에 빙의되지 않은 경우에는 실행하지 않게하자.
	{
		return;
	}

	PlayCharacter->Run();
}

void AMyPlayerController::StopRun()
{
	if (!myCharacter)
	{
		return;
	}

	if (myCharacter->CurrentState == EPlayerState::ALIVE)
	{
		StopRunToServer(myCharacter);
	}
}

void AMyPlayerController::StopRunToServer_Implementation(AMyCharacter* PlayCharacter)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	for (AActor* OutActor : OutActors)
	{
		AMyPlayerController* PC = Cast<AMyPlayerController>(OutActor);
		if (PC)
		{
			PC->StopRunToClient(PlayCharacter);
		}
	}
}

void AMyPlayerController::StopRunToClient_Implementation(AMyCharacter* PlayCharacter)
{
	if (PlayCharacter == NULL) // 캐릭터에 빙의되지 않은 경우에는 실행하지 않게하자.
	{
		return;
	}

	PlayCharacter->StopRun();
}

void AMyPlayerController::DanceComplete()
{
	if (!myCharacter)
	{
		return;
	}

	nMissionComplete++;

	AGameMain_HUD* HUD = GetHUD<AGameMain_HUD>();
	if (HUD == nullptr) return;

	HUD->SetPlayerMissionClear(nMissionComplete);

	if (nMissionComplete == 50)
	{
		bWinner = true;
	}
}

void AMyPlayerController::Dancing()
{
	if (!myCharacter)
	{
		return;
	}

	if (myCharacter->CurrentState == EPlayerState::ALIVE)
	{
		DancingToServer(myCharacter);
	}
}

void AMyPlayerController::DancingToServer_Implementation(AMyCharacter* PlayCharacter)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	for (AActor* OutActor : OutActors)
	{
		AMyPlayerController* PC = Cast<AMyPlayerController>(OutActor);
		if (PC)
		{
			PC->DancingToClient(PlayCharacter);
		}
	}
}

void AMyPlayerController::DancingToClient_Implementation(AMyCharacter* PlayCharacter)
{
	if (PlayCharacter == NULL) // 캐릭터에 빙의되지 않은 경우에는 실행하지 않게하자.
	{
		return;
	}

	PlayCharacter->Dancing();
}

void AMyPlayerController::StopDancing()
{
	if (!myCharacter)
	{
		return;
	}

	if (myCharacter->CurrentState == EPlayerState::ALIVE)
	{
		StopDancingToServer(myCharacter);
	}
}

void AMyPlayerController::StopDancingToServer_Implementation(AMyCharacter* PlayCharacter)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	for (AActor* OutActor : OutActors)
	{
		AMyPlayerController* PC = Cast<AMyPlayerController>(OutActor);
		if (PC)
		{
			PC->StopDancingToClient(PlayCharacter);
		}
	}
}

void AMyPlayerController::StopDancingToClient_Implementation(AMyCharacter* PlayCharacter)
{
	if (PlayCharacter == NULL) // 캐릭터에 빙의되지 않은 경우에는 실행하지 않게하자.
	{
		return;
	}

	PlayCharacter->StopDancing();
}

void AMyPlayerController::Attack()
{
	if (!myCharacter)
	{
		return;
	}

	if (myCharacter->CurrentState == EPlayerState::ALIVE)
	{
		AttackToServer(myCharacter);
	}
}

void AMyPlayerController::AttackToServer_Implementation(AMyCharacter* PlayCharacter)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	for (AActor* OutActor : OutActors)
	{
		AMyPlayerController* PC = Cast<AMyPlayerController>(OutActor);
		if (PC)
		{
			PC->AttackToClient(PlayCharacter);
		}
	}
}

void AMyPlayerController::AttackToClient_Implementation(AMyCharacter* PlayCharacter)
{
	if (PlayCharacter == NULL) // 캐릭터에 빙의되지 않은 경우에는 실행하지 않게하자.
	{
		return;
	}

	PlayCharacter->Attack();
}

void AMyPlayerController::CharacterDead()
{
	DeadToServer(myCharacter);
}

void AMyPlayerController::DeadToServer_Implementation(AMyCharacter* PlayCharacter)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	for (AActor* OutActor : OutActors)
	{
		AMyPlayerController* PC = Cast<AMyPlayerController>(OutActor);
		if (PC)
		{
			PC->DeadToClient(PlayCharacter);
		}
	}
}

void AMyPlayerController::DeadToClient_Implementation(AMyCharacter* PlayCharacter)
{
	if (PlayCharacter == NULL) // 캐릭터에 빙의되지 않은 경우에는 실행하지 않게하자.
	{
		return;
	}

	PlayCharacter->CharacterAnim->SetDeadAnim();

	DeathCount++;
}

void AMyPlayerController::GameOver()
{
	if (!myCharacter)
	{
		return;
	}

	UABGameInstance* MyGI = Cast<UABGameInstance>(GetGameInstance());
	FString WinnerName = MyGI->GetUserName("Player");
	GameoverToServer(WinnerName);
}

void AMyPlayerController::GameoverToServer_Implementation(const FString& WinnerName)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	for (AActor* OutActor : OutActors)
	{
		AMyPlayerController* PC = Cast<AMyPlayerController>(OutActor);
		if (PC)
		{
			PC->GameoverToClient(WinnerName);
		}
	}
}

void AMyPlayerController::GameoverToClient_Implementation(const FString& WinnerName)
{
	AGameMain_HUD* HUD = GetHUD<AGameMain_HUD>();
	if (HUD == nullptr) return;

	HUD->SetWinnerName(WinnerName);
	HUD->VisibleGameover();
	SetShowMouseCursor(true);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Gameover!"));
}

void AMyPlayerController::PlayerDeath()
{
	if (!myCharacter)
	{
		return;
	}

	DeadToServer(myCharacter);

	AGameMain_HUD* HUD = GetHUD<AGameMain_HUD>();
	if (HUD == nullptr) return;

	HUD->VisibleDeath();
	SetShowMouseCursor(true);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Dead!"));
}

void AMyPlayerController::SendMessage(const FText& Text)
{
	// GameInstance에 저장해두었던 내 닉네임.
	UABGameInstance* MyGI = GetGameInstance<UABGameInstance>(); // GameInstance를 직접 만들어서 사용
	if (MyGI)
	{
		FString UserName = MyGI->GetUserName("Player");
		FString Message = FString::Printf(TEXT("%s : %s"), *UserName, *Text.ToString());

		CtoS_SendMessage(Message); // 서버에서 실행될 수 있도록 보낸다.
	}
}

void AMyPlayerController::FocusChatInputText()
{
	AGameMain_HUD* HUD = GetHUD<AGameMain_HUD>();
	if (HUD == nullptr) return;

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(HUD->GetChatInputTextObject());

	SetInputMode(InputMode);
}

void AMyPlayerController::FocusGame()
{
	SetInputMode(FInputModeGameOnly());
}

void AMyPlayerController::CtoS_SendMessage_Implementation(const FString& Message)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);
	for (AActor* OutActor : OutActors)
	{
		AMyPlayerController* PC = Cast<AMyPlayerController>(OutActor);
		if (PC)
		{
			PC->StoC_SendMessage(Message);
		}
	}
}

void AMyPlayerController::StoC_SendMessage_Implementation(const FString& Message)
{
	// 서버와 클라이언트는 이 이벤트를 받아서 실행한다.
	AGameMain_HUD* HUD = GetHUD<AGameMain_HUD>();
	if (HUD == nullptr) return;

	HUD->AddChatMessage(Message);
}

void AMyPlayerController::EnterGameReady(bool bServer)
{
	AGameMain_HUD* HUD = GetHUD<AGameMain_HUD>();
	if (HUD == nullptr) return;

	HUD->InitServerUI(bServer);
}

void AMyPlayerController::ReadyStart()
{
	ReadyStartToServer();
}

void AMyPlayerController::ReadyStartToServer_Implementation()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	int nIndex = 0;

	for (AActor* OutActor : OutActors)
	{
		AMyPlayerController* PC = Cast<AMyPlayerController>(OutActor);
		if (PC)
		{
			// 서버에서 캐릭터의 위치를 정하고 클라이언트 들에게 그 위치에 설정하도록 하자
			PC->ReadyStartToClient(nIndex, OutActors.Num());
			nIndex++;
		}
	}
}

void AMyPlayerController::ReadyStartToClient_Implementation(int ServerNumber, int PlayerCount)
{
	AGameMain_HUD* HUD = GetHUD<AGameMain_HUD>();
	if (HUD == nullptr) return;

	if (myCharacter)
	{
		UABGameInstance* MyGI = Cast<UABGameInstance>(GetGameInstance());

		StartLocation = MyGI->GetLocation(ServerNumber);
		myCharacter->SetActorLocation(StartLocation);
		DefaultCount = PlayerCount;
		bStart = true;
		StartCharacter(myCharacter, StartLocation, MyGI->GetPlayerMesh("Player"), MyGI->GetUserName("Player"));
	}

	HUD->HiddenGameReady();

	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());
}

void AMyPlayerController::StartCharacter(AMyCharacter* PlayCharacter, FVector CharacterLocation, USkeletalMesh* CharacterMesh, const FString& PlayerName)
{
	StartCharacterToServer(PlayCharacter, CharacterLocation, CharacterMesh, PlayerName);
}

void AMyPlayerController::StartCharacterToServer_Implementation(AMyCharacter* PlayCharacter, FVector CharacterLocation, USkeletalMesh* CharacterMesh, const FString& PlayerName)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	for (AActor* OutActor : OutActors)
	{
		AMyPlayerController* PC = Cast<AMyPlayerController>(OutActor);
		if (PC)
		{
			// 서버에서 캐릭터의 위치를 정하고 클라이언트 들에게 그 위치에 설정하도록 하자
			PC->StartCharacterToClient(PlayCharacter, CharacterLocation, CharacterMesh, PlayerName);
		}
	}
}

void AMyPlayerController::StartCharacterToClient_Implementation(AMyCharacter* PlayCharacter, FVector CharacterLocation, USkeletalMesh* CharacterMesh, const FString& PlayerName)
{
	PlayCharacter->SetActorLocation(CharacterLocation);
	PlayCharacter->mySkeletalMesh->SetSkeletalMesh(CharacterMesh);
	PlayCharacter->PlayerName = PlayerName;
}

void AMyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerController, myCharacter);
	DOREPLIFETIME(AMyPlayerController, DeathCount);
	DOREPLIFETIME(AMyPlayerController, DefaultCount);
	DOREPLIFETIME(AMyPlayerController, nPlayerNumber);
	DOREPLIFETIME(AMyPlayerController, StartLocation);
	DOREPLIFETIME(AMyPlayerController, bStart);
	DOREPLIFETIME(AMyPlayerController, nMissionComplete);
	DOREPLIFETIME(AMyPlayerController, bWinner);
}
