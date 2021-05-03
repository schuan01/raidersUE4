// Fill out your copyright notice in the Description page of Project Settings.


#include "RaidersBaseAltar.h"

// Sets default values
ARaidersBaseAltar::ARaidersBaseAltar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("altarMesh"));
	mainMesh->SetupAttachment(RootComponent);
	mainMesh->bEditableWhenInherited = true;

	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AltarCollision"));
	boxCollision->SetupAttachment(mainMesh);
	boxCollision->bEditableWhenInherited = true;

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("planePressButton"));
	plane->SetupAttachment(mainMesh);
	plane->bEditableWhenInherited = true;
}

// Called when the game starts or when spawned
void ARaidersBaseAltar::BeginPlay()
{
	Super::BeginPlay();
	boxCollision->OnComponentBeginOverlap.AddDynamic(this, &ARaidersBaseAltar::OnOverlapBeginBoxCollision);
	boxCollision->OnComponentEndOverlap.AddDynamic(this, &ARaidersBaseAltar::OnOverlapEndBoxCollision);

	plane->SetVisibility(false);
	
}

// Called every frame
void ARaidersBaseAltar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARaidersBaseAltar::OnOverlapBeginBoxCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.  
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ARaidersBaseCharacter* mainPlayer = Cast<ARaidersBaseCharacter>(OtherActor);
		if (mainPlayer != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("BeginOverlap %s"), *mainPlayer->GetName());

			//Set visibility of the Plane to True
			plane->SetVisibility(true);
		}
		
	}
}

void ARaidersBaseAltar::OnOverlapEndBoxCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.  
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ARaidersBaseCharacter* mainPlayer = Cast<ARaidersBaseCharacter>(OtherActor);
		if (mainPlayer != nullptr) 
		{
			UE_LOG(LogTemp, Warning, TEXT("EndOverlap %s"), *mainPlayer->GetName());

			//Set visibility of the Plane to True
			plane->SetVisibility(false);
		}
	}
}

