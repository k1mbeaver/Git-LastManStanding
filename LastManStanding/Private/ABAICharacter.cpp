// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAICharacter.h"
#include "ABAnimInstance.h"
#include "ABAIController.h"
#include "ABGameInstance.h"
#include <random>

// Sets default values
AABAICharacter::AABAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_EASYMODEL(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	if (SK_EASYMODEL.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_EASYMODEL.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> PLAYER_ANIM(TEXT("/Game/Mannequin/Animations/PersonAnimBlueprint"));
	if (PLAYER_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PLAYER_ANIM.Class);
	}

	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	AIControllerClass = AABAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	SetActorHiddenInGame(false);

}

void AABAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


// Called when the game starts or when spawned
void AABAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UABGameInstance* MyGI = Cast<UABGameInstance>(GetGameInstance());
	int nRandomNum = RandomMesh(0, 3);


	ABAIController = Cast<AABAIController>(GetController());
	GetMesh()->SetSkeletalMesh(MyGI->GetSkeletalMesh(ArrMeshName[nRandomNum]));
	GetMesh()->SetAnimInstanceClass(MyGI->GetAninInstance(ArrMeshName[nRandomNum]));
	ABAnim = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AABAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AABAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AABAICharacter::CharacterDead()
{
	ABAIController->StopAI();
	MultiDead(this);
}

float AABAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (FinalDamage > 0.0f) // 일단 맞으면 기절
	{
		CharacterDead();
	}

	return FinalDamage;
}

int AABAICharacter::RandomMesh(int min, int max)
{
	std::random_device rd;
	std::mt19937_64 rEngine(rd());
	std::uniform_int_distribution<>dist(min, max);
	return static_cast<int>(dist(rEngine));
}
void AABAICharacter::MultiDead_Implementation(AABAICharacter* DeathCharacter)
{
	DeathCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DeathCharacter->GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	DeathCharacter->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	DeathCharacter->ABAnim->SetDeadAnim();
}

void AABAICharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AABAICharacter, ABAnim);
}