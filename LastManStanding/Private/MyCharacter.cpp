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
#include "DrawDebugHelpers.h"
#include "NavigationSystem.h"

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

	AttackRange = 50.0f;
	AttackRadius = 25.0;
	AttackPower = 100.0f;

	CurrentState = EPlayerState::ALIVE;

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

	mySkeletalMesh->SetSkeletalMesh(MyGI->GetPlayerMesh("Player"));
	mySkeletalMesh->SetAnimInstanceClass(MyGI->GetPlayerAnim("Player"));
	CharacterAnim = Cast<UABAnimInstance>(mySkeletalMesh->GetAnimInstance());
	AttackMontage = MyGI->GetMontage("Attack");
	DanceMontage = MyGI->GetMontage("Dance");

	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->MaxWalkSpeed = fCurrentWalkSpeed;

	CharacterAnim->OnOnCollisonStart_Punch.AddUObject(this, &AMyCharacter::AttackCheck);
	CharacterAnim->DancingEnd_Mission.AddUObject(this, &AMyCharacter::DanceComplete);
	
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

	if (!bCanMove)
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

	if (!bCanMove)
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

	if (!bCanMove)
	{
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed = fCurrentRunSpeed;
}

void AMyCharacter::StopRun()
{
	if (this == nullptr)
	{
		return;
	}

	if (!bCanMove)
	{
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed = fCurrentWalkSpeed;
}

void AMyCharacter::Jump()
{
	if (this == nullptr)
	{
		return;
	}

	if (!bCanMove)
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

	if (!bCanMove)
	{
		return;
	}

	Super::StopJumping();
}

void AMyCharacter::Dancing()
{
	if (this == nullptr)
	{
		return;
	}

	bCanMove = false;
	CharacterAnim->PlayDanceMontage(DanceMontage);
}

void AMyCharacter::DanceComplete()
{
	if (this == nullptr)
	{
		return;
	}

	bCanMove = true;
	CharacterAnim->StopAllMontages(true);

	//MyPC = Cast<AMyPlayerController>(GetController());

/*
	if (MyPC == nullptr)
	{
		MyPC = Cast<AMyPlayerController>(GetController());
	}
*/

	//MyPC->DanceComplete();
}

void AMyCharacter::StopDancing()
{
	if (this == nullptr)
	{
		return;
	}

	bCanMove = true;
	CharacterAnim->StopAllMontages(true);
}

void AMyCharacter::Attack()
{
	if (this == nullptr)
	{
		return;
	}

	if (IsAttacking == true)
	{
		return;
	}
	UABGameInstance* MyGI = Cast<UABGameInstance>(GetGameInstance());

	CharacterAnim->PlayAttackMontage(AttackMontage);
}

void AMyCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, // Attack 채널 
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

/*
#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 3.0f;

	// 이거는 에디터에서만 사용하는거

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("PlayerPunch!")); // 플레이어가 펀치하는지 확인용

#endif
*/
	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(AttackPower, DamageEvent, GetController(), this);
		}
	}
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (FinalDamage > 0.0f) // 일단 맞으면 기절
	{
		CharacterDead();
	}

	return FinalDamage;
}

void AMyCharacter::CharacterDead()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("CharacterDead!"));
	CurrentState = EPlayerState::DEAD;
	MyPC = Cast<AMyPlayerController>(GetController());
	MyPC->PlayerDeath();
	MultiDead(this);
}

void AMyCharacter::MultiDead_Implementation(AMyCharacter* DeathCharacter)
{
	DeathCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DeathCharacter->GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	DeathCharacter->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	DeathCharacter->CharacterAnim->SetDeadAnim();
}

void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyCharacter, fCurrentWalkSpeed);
	DOREPLIFETIME(AMyCharacter, fCurrentRunSpeed);
	DOREPLIFETIME(AMyCharacter, CharacterAnim);
	DOREPLIFETIME(AMyCharacter, mySkeletalMesh);
	DOREPLIFETIME(AMyCharacter, AttackMontage);
	DOREPLIFETIME(AMyCharacter, CurrentState);
	DOREPLIFETIME(AMyCharacter, AttackPower);
	DOREPLIFETIME(AMyCharacter, StartLocation);
	DOREPLIFETIME(AMyCharacter, PlayerName);
	DOREPLIFETIME(AMyCharacter, DanceMontage);
}