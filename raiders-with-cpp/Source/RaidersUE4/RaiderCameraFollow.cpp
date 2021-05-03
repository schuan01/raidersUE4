// Fill out your copyright notice in the Description page of Project Settings.


#include "RaiderCameraFollow.h"

// Sets default values
ARaiderCameraFollow::ARaiderCameraFollow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bEditableWhenInherited = true;
	
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	MainCamera->SetupAttachment(SpringArm);
	MainCamera->bEditableWhenInherited = true;

	SpringArm->TargetArmLength = 1500.0f;
	SpringArm->bDoCollisionTest = false;

	InterpSpeed = 10.0f;

}

// Called when the game starts or when spawned
void ARaiderCameraFollow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARaiderCameraFollow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateCamera();

}

void ARaiderCameraFollow::UpdateCamera()
{
	//START TO FOLLOW
	if (PlayerToFollow != nullptr)
	{
		this->TargetPos = PlayerToFollow->GetActorLocation();
		
		FVector newLoc = FMath::VInterpTo(PreviousPos, TargetPos, GetWorld()->DeltaTimeSeconds, InterpSpeed);
		this->SetActorLocation(newLoc);

		this->PreviousPos = this->GetActorLocation();
	}
}

void ARaiderCameraFollow::NewPlayerJoin(APlayerController* newPlayerController, ARaidersMainPlayer* playerSpawn)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetNameSafe(newPlayerController));
	this->bIsUsed = true;
	newPlayerController->SetViewTargetWithBlend(this);
	this->PlayerToFollow = playerSpawn;
}

