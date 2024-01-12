// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCamera.h"
#include "Camera/CameraComponent.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyCamera::AMyCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
}

// Called when the game starts or when spawned
void AMyCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCamera::PlayerCameraChange()
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());

	if (PlayerController)
	{
		float CameraSwitchDelay = 0.1f; // The duration after which the camera will switch back
		PlayerController->SetViewTargetWithBlend(this, 0.1f);
	}
}