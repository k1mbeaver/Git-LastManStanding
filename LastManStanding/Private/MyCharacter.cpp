// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "ABAnimInstance.h"
#include "ABGameInstance.h"
#include "MyPlayerController.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	mySkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MYMESH"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	mySkeletalMesh->SetupAttachment(GetCapsuleComponent());

	mySkeletalMesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));

	// 회전속도를 함께 지정해 이동 방향으로 캐릭터가 부드럽게 회저하도록 기능을 추가한다.
	// 캐릭터가 자연스럽게 회전하게 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UABGameInstance* MyGI = Cast<UABGameInstance>(GetGameInstance());

	mySkeletalMesh->SetSkeletalMesh(MyGI->GetSkeletalMesh("Default"));
	mySkeletalMesh->SetAnimInstanceClass(MyGI->GetAninInstance("Default"));

	fCurrentPawnSpeed = 200.0f;
	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->MaxWalkSpeed = fCurrentPawnSpeed;
	
	/*
	SpringArm->TargetArmLength = 450.0f;
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;
	*/
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::UpDown(float NewAxisValue)
{
	if (this == nullptr)
	{
		return;
	}

	FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X);

	Direction.Z = 0.0f;
	Direction.Normalize();

	AddMovementInput(Direction, NewAxisValue);
}

void AMyCharacter::LeftRight(float NewAxisValue)
{
	if (this == nullptr)
	{
		return;
	}

	FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y);

	Direction.Z = 0.0f;
	Direction.Normalize();

	AddMovementInput(Direction, NewAxisValue);
}

void AMyCharacter::LookUp(float NewAxisValue)
{
	if (this == nullptr)
	{
		return;
	}

	AddControllerPitchInput(NewAxisValue);
}

void AMyCharacter::Turn(float NewAxisValue)
{
	if (this == nullptr)
	{
		return;
	}

	AddControllerYawInput(NewAxisValue);
}

void AMyCharacter::Run()
{
	if (this == nullptr)
	{
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed = fCurrentPawnSpeed * 2.0f;
}

void AMyCharacter::StopRun()
{
	if (this == nullptr)
	{
		return;
	}
	GetCharacterMovement()->MaxWalkSpeed = fCurrentPawnSpeed / 2.0f;
}

void AMyCharacter::Jump()
{
	if (this == nullptr)
	{
		return;
	}

	Super::Jump();
}

void AMyCharacter::StopJumping()
{
	if (this == nullptr)
	{
		return;
	}

	Super::StopJumping();
}

void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyCharacter, fCurrentPawnSpeed);
	DOREPLIFETIME(AMyCharacter, CharacterAnim);
	DOREPLIFETIME(AMyCharacter, mySkeletalMesh);
}