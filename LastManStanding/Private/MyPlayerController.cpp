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
		SetInputMode(FInputModeGameOnly());
		myCharacter->MyPC = this;
		myCharacter->EnableInput(this);
	}
}

void AMyPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Possess!"));
}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


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
	//InputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &AMyPlayerController::Run);
	//InputComponent->BindAction(TEXT("Run"), IE_Released, this, &AMyPlayerController::StopRun);

	// 캐릭터 점프
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

void AMyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerController, myCharacter);
}