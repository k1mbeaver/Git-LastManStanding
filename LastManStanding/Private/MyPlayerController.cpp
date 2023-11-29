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
	myCharacter->MyPC = this;
}

void AMyPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Possess!"));
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());
}


void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bGameStart)
	{
		if (CurrentPlayer == 1)
		{
			if (myCharacter->CurrentState == EPlayerState::ALIVE)
			{
				GameOver();
			}

			bGameStart = false;
		}
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

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
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

		nPlayerNumber = OutActors.Num() - 1;
		
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
			PlayCharacter->fCurrentPawnSpeed = 200.0f;

			PC->CurrentPlayer = OutActors.Num();

			if (PC->CurrentPlayer > 1)
			{
				PC->bGameStart = true;
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("GameStart!"));
			}

			PC->PlayerEnterToClient(PlayCharacter, OutActors.Num());
		}
	}
}

void AMyPlayerController::PlayerEnterToClient_Implementation(AMyCharacter* PlayCharacter, int nCurrentPlayer)
{
	if (PlayCharacter == NULL) // 캐릭터에 빙의되지 않은 경우에는 실행하지 않게하자.
	{
		return;
	}

	CurrentPlayer = nCurrentPlayer;

	if (CurrentPlayer > 1)
	{
		bGameStart = true;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("GameStart!"));
	}
	PlayCharacter->fCurrentPawnSpeed = 200.0f;
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
			PC->CurrentPlayer = PC->CurrentPlayer - 1;
		}
	}
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
}

void AMyPlayerController::GameOver()
{
	if (!myCharacter)
	{
		return;
	}

	UABGameInstance* MyGI = Cast<UABGameInstance>(GetGameInstance());
	GameoverToServer(MyGI->GetUserName("Player"));
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
}

void AMyPlayerController::PlayerDeath()
{
	if (!myCharacter)
	{
		return;
	}

	PlayerDeathToServer();

	AGameMain_HUD* HUD = GetHUD<AGameMain_HUD>();
	if (HUD == nullptr) return;

	HUD->VisibleDeath();
	SetShowMouseCursor(true);
}

void AMyPlayerController::PlayerDeathToServer_Implementation()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);

	for (AActor* OutActor : OutActors)
	{
		AMyPlayerController* PC = Cast<AMyPlayerController>(OutActor);
		if (PC)
		{
			PC->CurrentPlayer = PC->CurrentPlayer - 1;
		}
	}
}

void AMyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerController, myCharacter);
	DOREPLIFETIME(AMyPlayerController, CurrentPlayer);
	DOREPLIFETIME(AMyPlayerController, bGameStart);
	DOREPLIFETIME(AMyPlayerController, nPlayerNumber);
}
