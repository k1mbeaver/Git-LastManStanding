// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerController.h"
#include "GameMain_HUD.h"
#include "ABAnimInstance.h"
#include "ABCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "ABGameInstance.h"
#include "Kismet/KismetMathLibrary.h"

AABPlayerController::AABPlayerController()
{
	//fSprintSpeedMultiPlayer = 3.0f; // 처음은 3.0, 미션수행시 2.5 2.0 1.5 단계로 줄어듬 
}

void AABPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AABPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (aPawn)
	{
		myCharacter = Cast<AABCharacter>(aPawn);
		myCharacter->MyCharacterDead.AddUObject(this, &AABPlayerController::PlayerKill); // 내 캐릭터가 죽었다는 델리게이트 함수가 발생하면?
		PlayerEnter();
		SetInputMode(FInputModeGameOnly());
	}
}

void AABPlayerController::PlayerEnter()
{
	CtoS_PlayerEnter();
}

void AABPlayerController::CtoS_PlayerEnter_Implementation()
{
	TArray<AActor*> OutActors;
	int PlayerCount = 0;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);
	for (AActor* OutActor : OutActors)
	{
		AABPlayerController* PC = Cast<AABPlayerController>(OutActor);
		if (PC)
		{
			++PlayerCount;
		}
	}
	myCharacter->nNowPlayer = PlayerCount;
	for (AActor* OutActor : OutActors)
	{
		AABPlayerController* PC = Cast<AABPlayerController>(OutActor);
		if (PC)
		{
			PC->StoC_PlayerEnter(myCharacter->nNowPlayer);
		}
	}
}

void AABPlayerController::StoC_PlayerEnter_Implementation(int PlayerCount)
{
	if (myCharacter == NULL) // 캐릭터에 빙의되지 않은 경우에는 실행하지 않게하자.
	{
		return;
	}
	myCharacter->nNowPlayer = PlayerCount;
	FString testPlayerCount = FString::FromInt(myCharacter->nNowPlayer);
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, testPlayerCount);
}

void AABPlayerController::PlayerKill()
{
	CtoS_PlayerKill(); // 클라이언트에서 호출하고 서버에서 실행하는 함수
}

void AABPlayerController::CtoS_PlayerKill_Implementation()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);
	myCharacter->nPlayerKill++;
	for (AActor* OutActor : OutActors)
	{
		AABPlayerController* PC = Cast<AABPlayerController>(OutActor);
		if (PC)
		{
			PC->StoC_PlayerKill(myCharacter->nPlayerKill); // 서버에서는 모든 클라이언트들에게 이 함수를 실행하라고한다.
		}
	}
}

void AABPlayerController::StoC_PlayerKill_Implementation(int nPlayerKill)
{
	if (myCharacter == NULL) // 캐릭터에 빙의되지 않은 경우에는 실행하지 않게하자.
	{
		return;
	}
	myCharacter->nPlayerKill = nPlayerKill;
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, testPlayerCount);
}





void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(false);
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}

void AABPlayerController::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (myCharacter->nKillingCharacter == 10 || myCharacter->nPlayerKill == myCharacter->nNowPlayer - 1)
	{
		UABGameInstance* MyGI = GetGameInstance<UABGameInstance>(); // GameInstance를 직접 만들어서 사용
		FString UserName = MyGI->GetUserName("Player");

		GameEnd(UserName);
	}
}


void AABPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//AABCharacter* myCharacter = Cast<AABCharacter>(myPawn);

	// 키 바인딩

	InputComponent->BindAction(TEXT("Chat"), EInputEvent::IE_Pressed, this, &AABPlayerController::FocusChatInputText);

	// 움직임

	//InputComponent->BindAxis(TEXT("UpDown"), this, &AABPlayerController::UpDown);
	//InputComponent->BindAxis(TEXT("LeftRight"), this, &AABPlayerController::LeftRight);
	//InputComponent->BindAxis(TEXT("LookUp"), this, &AABPlayerController::LookUp);
	//InputComponent->BindAxis(TEXT("Turn"), this, &AABPlayerController::Turn);

	// 액션

	InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AABPlayerController::Jump);
	InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &AABPlayerController::StopJumping);
	InputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AABPlayerController::Attack);
	InputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &AABPlayerController::Run);
	InputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &AABPlayerController::StopRun);
}

// 움직임 함수
/*
void AABPlayerController::UpDown(float NewAxisValue)
{
	if (myCharacter != nullptr)
	{
		myCharacter->UpDown(NewAxisValue);
	}
}

void AABPlayerController::LeftRight(float NewAxisValue)
{
	if (myCharacter != nullptr)
	{
		myCharacter->LeftRight(NewAxisValue);
	}
}


void AABPlayerController::LookUp(float NewAxisValue)
{
	if (myCharacter != nullptr)
	{
		myCharacter->LookUp(NewAxisValue);
	}
}

void AABPlayerController::Turn(float NewAxisValue)
{
	if (myCharacter != nullptr)
	{
		myCharacter->Turn(NewAxisValue);
	}
}
*/
// 액션 함수

void AABPlayerController::Jump()
{
	if (myCharacter == nullptr) return;

	myCharacter->Jump();
}

void AABPlayerController::StopJumping()
{
	if (myCharacter == nullptr) return;

	myCharacter->StopJumping();
}

void AABPlayerController::CheckMission()
{
	if (bMissionClear == false && myCharacter->nMissionClear == 1) // 캐릭터 체크하는건 뒤로둬서 bool 다를땐 안하게끔
	{
		SetPlayerMissionClear(myCharacter->nMissionClear);

		// 여기서 달리기 못하게 하고 속도 고정
		bCanRun = false;
		bMissionClear = true; // 다시 실행안되게끔
	}
}

// 달리기
void AABPlayerController::Run()
{
	//APawn* const myPawn = GetPawn();
	//AABCharacter* myCharacter = Cast<AABCharacter>(myPawn);

	//myCharacter->GetCharacterMovement()->MaxWalkSpeed *= myCharacter->fSprintSpeedMultiPlayer;

	if (myCharacter->CurrentState == ECharacterState::READY && bCanRun == true)
	{
		if (myCharacter == nullptr) return;
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("PlayerRun!"));

		CtoS_Run(myCharacter);
		//MyRun.Broadcast();
	}
}

void AABPlayerController::CtoS_Run_Implementation(AABCharacter* ClientCharacter)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);
	for (AActor* OutActor : OutActors)
	{
		AABPlayerController* PC = Cast<AABPlayerController>(OutActor);
		if (PC)
		{
			PC->StoC_Run(ClientCharacter);
		}
	}
}

void AABPlayerController::StoC_Run_Implementation(AABCharacter* ClientCharacter)
{
	// 서버와 클라이언트는 이 이벤트를 받아서 실행한다.

	if (ClientCharacter == nullptr) return;

	if (bCanRun == false)
	{
		myCharacter->GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	}

	ClientCharacter->GetCharacterMovement()->MaxWalkSpeed *= ClientCharacter->fSprintSpeedMultiPlayer;
	
}

void AABPlayerController::StopRun()
{
	//APawn* const myPawn = GetPawn();
	//AABCharacter* myCharacter = Cast<AABCharacter>(myPawn);
	//myCharacter->GetCharacterMovement()->MaxWalkSpeed /= myCharacter->fSprintSpeedMultiPlayer;


	if (myCharacter->CurrentState == ECharacterState::READY && bCanRun == true)
	{
		if (myCharacter == nullptr) return;
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("PlayerStopRun!"));

		CtoS_StopRun(myCharacter);
		//MyStopRun.Broadcast();
	}
}

void AABPlayerController::CtoS_StopRun_Implementation(AABCharacter* ClientCharacter)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);
	for (AActor* OutActor : OutActors)
	{
		AABPlayerController* PC = Cast<AABPlayerController>(OutActor);
		if (PC)
		{
			PC->StoC_StopRun(ClientCharacter);
		}
	}
}

void AABPlayerController::StoC_StopRun_Implementation(AABCharacter* ClientCharacter)
{
	// 서버와 클라이언트는 이 이벤트를 받아서 실행한다.
	if (ClientCharacter == nullptr) return;

	if (bCanRun == false)
	{
		myCharacter->GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	}

	ClientCharacter->GetCharacterMovement()->MaxWalkSpeed /= ClientCharacter->fSprintSpeedMultiPlayer;

}
// 채팅

void AABPlayerController::SendMessage(const FText& Text)
{
	// GameInstance에 저장해두었던 내 닉네임.
	UABGameInstance* MyGI = GetGameInstance<UABGameInstance>(); // GameInstance를 직접 만들어서 사용
	if (MyGI) 
   {
		FString UserName = MyGI->GetUserName("Player");
		FString Message = FString::Printf(TEXT("%s : %s"), *UserName, *Text.ToString());

		CtoS_SendMessage(Message); // 서버에서 실행될 수 있도록 보낸다.
   }
	//FString Message = FString::Printf(TEXT("%s"), *Text.ToString());

	//CtoS_SendMessage(Message); // 서버에서 실행될 수 있도록 보낸다.
}

void AABPlayerController::FocusChatInputText()
{
	AGameMain_HUD* HUD = GetHUD<AGameMain_HUD>();
	if (HUD == nullptr) return;

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(HUD->GetChatInputTextObject());

	SetInputMode(InputMode);
}

void AABPlayerController::FocusGame()
{
	SetInputMode(FInputModeGameOnly());
}

// 미션

void AABPlayerController::SetPlayerMissionClear(int nMissionClear)
{
	AGameMain_HUD* HUD = GetHUD<AGameMain_HUD>();
	if (HUD == nullptr) return;
	HUD->SetPlayerMissionClear(nMissionClear);
}

// 게임 끝

void AABPlayerController::SetWinnerName(const FString& WinnerName)
{
	AGameMain_HUD* HUD = GetHUD<AGameMain_HUD>();
	if (HUD == nullptr) return;
	HUD->SetWinnerName(WinnerName);
}

void AABPlayerController::VisibleGameover()
{
	AGameMain_HUD* HUD = GetHUD<AGameMain_HUD>();
	if (HUD == nullptr) return;
	HUD->VisibleGameover();
}

void AABPlayerController::CtoS_GameEnd_Implementation(const FString& WinnerName)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);
	for (AActor* OutActor : OutActors)
	{
		AABPlayerController* PC = Cast<AABPlayerController>(OutActor);
		if (PC)
		{
			PC->StoC_GameEnd(WinnerName);
		}
	}
}

void AABPlayerController::StoC_GameEnd_Implementation(const FString& WinnerName)
{
	AGameMain_HUD* HUD = GetHUD<AGameMain_HUD>();

	if (HUD == nullptr) return;

	HUD->SetWinnerName(WinnerName);
	HUD->VisibleGameover();
	SetShowMouseCursor(true);
}

void AABPlayerController::GameEnd(const FString& WinnerName)
{
	CtoS_GameEnd(WinnerName);
}

// 채팅(서버)

void AABPlayerController::CtoS_SendMessage_Implementation(const FString& Message)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);
	for (AActor* OutActor : OutActors)
	{
		AABPlayerController* PC = Cast<AABPlayerController>(OutActor);
		if (PC)
		{
			PC->StoC_SendMessage(Message);
		}
	}
}

void AABPlayerController::StoC_SendMessage_Implementation(const FString& Message)
{
	// 서버와 클라이언트는 이 이벤트를 받아서 실행한다.
	AGameMain_HUD* HUD = GetHUD<AGameMain_HUD>();
	if (HUD == nullptr) return;

	HUD->AddChatMessage(Message);
}

// 공격(서버)

void AABPlayerController::Attack()
{
	//APawn* const myPawn = GetPawn();
	//AABCharacter* myCharacter = Cast<AABCharacter>(myPawn);
	// 공격 중이면 다시 공격못하게함

	if (bCanDeligate == false)
	{
		myCharacter->ABAnim->OnMontageEnded.AddDynamic(this, &AABPlayerController::OnAttackMontageEnded);
		bCanDeligate = true;
	}
	if (myCharacter->IsAttacking) return;

	if (myCharacter->CurrentState == ECharacterState::READY)
	{
		if (myCharacter == nullptr) return;
		UAnimMontage* playPunch;

		// 이 부분에서 공격 몽타주를 실행한다.
		playPunch = myCharacter->ABAnim->GetAttackMontage();
		myCharacter->AttackPower = 100.0f;
		myCharacter->ABAnim->PlayAttackMontage(playPunch);
		myCharacter->IsAttacking = true;
		
		CtoS_Attack(myCharacter, playPunch);

		//FString testPlayerCount = FString::FromInt(myCharacter->nNowPlayer);
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, testPlayerCount);
		//MyStopRun.Broadcast();
	}
}

void AABPlayerController::CtoS_Attack_Implementation(AABCharacter* ClientCharacter, UAnimMontage* playPunch)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);
	for (AActor* OutActor : OutActors)
	{
		AABPlayerController* PC = Cast<AABPlayerController>(OutActor);
		if (PC)
		{
			PC->StoC_Attack(ClientCharacter, playPunch);
		}
	}
}

void AABPlayerController::StoC_Attack_Implementation(AABCharacter* ClientCharacter, UAnimMontage* playPunch)
{
	// 서버와 클라이언트는 이 이벤트를 받아서 실행한다.
	if (ClientCharacter->IsAttacking) return;

	ClientCharacter->AttackPower = 100.0f;
	ClientCharacter->ABAnim->PlayAttackMontage(playPunch);
	ClientCharacter->IsAttacking = true;

	/*
	if (ClientCharacter->DeathCharacter != NULL)
	{
		ClientCharacter->DeathCharacter->ABAnim->SetDeadAnim();
		//ClientCharacter->DeathCharacter->SetCharacterState(ECharacterState::DEAD);
		ClientCharacter->DeathCharacter->SetActorEnableCollision(false);
	    ClientCharacter->DeathCharacter = NULL;
	}
	*/
}

// 리플리케이트


void AABPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AABPlayerController, myCharacter);
	DOREPLIFETIME(AABPlayerController, myPawn);
	DOREPLIFETIME(AABPlayerController, bCanRun);
	DOREPLIFETIME(AABPlayerController, bMissionClear);
}

