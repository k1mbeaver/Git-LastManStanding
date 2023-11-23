// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ABGameInstance.h"
#include "Kismet/KismetMathLibrary.h"

AMyPlayerController::AMyPlayerController()
{

}

void AMyPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);


	if (aPawn)
	{
		myCharacter = Cast<AMyCharacter>(aPawn);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Success!"));
		myCharacter->MyPC = this;
		PlayerEnter();
	}
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


}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// ĳ���� �̵� �Լ�
	InputComponent->BindAxis(TEXT("UpDown"), this, &AMyPlayerController::UpDown);
	InputComponent->BindAxis(TEXT("LeftRight"), this, &AMyPlayerController::LeftRight);
	InputComponent->BindAxis(TEXT("LookUp"), this, &AMyPlayerController::LookUp);
	InputComponent->BindAxis(TEXT("Turn"), this, &AMyPlayerController::Turn);

	//ĳ���� �޸���
	InputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &AMyPlayerController::Run);
	InputComponent->BindAction(TEXT("Run"), IE_Released, this, &AMyPlayerController::StopRun);

	// ĳ���� ����
	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMyPlayerController::Jump);
	InputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AMyPlayerController::StopJumping);
}

void AMyPlayerController::UpDown(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->UpDown(NewAxisValue);
	}
}

void AMyPlayerController::LeftRight(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->LeftRight(NewAxisValue);
	}
}

void AMyPlayerController::LookUp(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->LookUp(NewAxisValue);
	}
}

void AMyPlayerController::Turn(float NewAxisValue)
{
	if (myCharacter)
	{
		myCharacter->Turn(NewAxisValue);
	}
}

void AMyPlayerController::Jump()
{
	if (myCharacter)
	{
		myCharacter->Jump();
	}
}

void AMyPlayerController::StopJumping()
{
	if (myCharacter)
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
			PlayCharacter->fCurrentPawnSpeed = 200.0f;
			PC->PlayerEnterToClient(PlayCharacter);
		}
	}
}

void AMyPlayerController::PlayerEnterToClient_Implementation(AMyCharacter* PlayCharacter)
{
	if (PlayCharacter == NULL) // ĳ���Ϳ� ���ǵ��� ���� ��쿡�� �������� �ʰ�����.
	{
		return;
	}

	PlayCharacter->fCurrentPawnSpeed = 200.0f;
}

void AMyPlayerController::Run()
{
	if (myCharacter)
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
	if (PlayCharacter == NULL) // ĳ���Ϳ� ���ǵ��� ���� ��쿡�� �������� �ʰ�����.
	{
		return;
	}

	PlayCharacter->Run();
}

void AMyPlayerController::StopRun()
{
	if (myCharacter)
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
	if (PlayCharacter == NULL) // ĳ���Ϳ� ���ǵ��� ���� ��쿡�� �������� �ʰ�����.
	{
		return;
	}

	PlayCharacter->StopRun();
}

void AMyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerController, myCharacter);
}