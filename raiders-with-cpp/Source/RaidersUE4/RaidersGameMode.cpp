// Fill out your copyright notice in the Description page of Project Settings.


#include "RaidersGameMode.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "RaidersMainPlayer.h"
#include "RaiderCameraFollow.h"
#include "Engine/EngineTypes.h"
#include <RaidersPlayerStart.h>

ARaidersGameMode::ARaidersGameMode()
{

}

void ARaidersGameMode::BeginPlay()
{
	//TODO
	//URaidersGameInstance* gameInstance = Cast<URaidersGameInstance>(GetGameInstance());
	//this->bIs1vs1 = gameInstance->bStateIs1VS1;
	this->bIs1vs1 = true;
	if (this->bIs1vs1)
	{
		this->maxPlayerCount = 1;//play 0 and player 1
	}
	else
	{
		this->maxPlayerCount = 3;//player 0,player 1,player 2, player 3
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARaidersPlayerStart::StaticClass(), allPlayersStartArray);

	EnableInput(UGameplayStatics::GetPlayerControllerFromID(GetWorld(), 0));//Keyboard player 1

	this->playersController.AddUnique(UGameplayStatics::GetPlayerControllerFromID(GetWorld(), 0));

	//The rest 3 players(previous keyvoard/pad + 3 pads

	for (size_t i = 0; i < this->maxPlayerCount; i++)
	{
		APlayerController* controller = UGameplayStatics::CreatePlayer(GetWorld(), -1, true);
		EnableInput(controller);
		this->playersController.AddUnique(controller);
	}

	if (this->bIs1vs1)
	{
		SpawnCharacter_Implementation(this->playersController[0], ETeam::TeamA);
		SpawnCharacter_Implementation(this->playersController[1], ETeam::TeamB);
	}
	else
	{
		SpawnCharacter_Implementation(this->playersController[0], ETeam::TeamA);
		SpawnCharacter_Implementation(this->playersController[1], ETeam::TeamA);
		SpawnCharacter_Implementation(this->playersController[2], ETeam::TeamB);
		SpawnCharacter_Implementation(this->playersController[3], ETeam::TeamB);
	}
}

void ARaidersGameMode::SpawnCharacter_Implementation(APlayerController* controller, ETeam team)
{
	if (controller->GetPawn() != nullptr)
	{
		controller->GetPawn()->Destroy();
		TArray<ARaidersPlayerStart*> starts;
		for (AActor* playerStart : this->allPlayersStartArray)
		{
			ARaidersPlayerStart* start = Cast<ARaidersPlayerStart>(playerStart);
			if (start->teamStart == team)
			{
				starts.Add(start);
			}
		}
		if (starts.Num() > 0)
		{
			int32 rand = FMath::RandRange(0, starts.Num() - 1);
			FActorSpawnParameters params;
			//TODO
			FVector location = starts[rand]->GetActorLocation();
			FRotator rotator = FRotator(0, -45, 0);
			FVector scale = FVector(1, 1, 1);

			FTransform transform = FTransform(rotator, location, scale);
			ARaidersMainPlayer* mainPlayer = GetWorld()->SpawnActor<ARaidersMainPlayer>(RaiderMainPlayerBP, location, rotator, params);
			if (mainPlayer != nullptr)
			{

				//ARaidersMainPlayer* mainPlayer = Cast<ARaidersMainPlayer>(spawn);
				controller->Possess(mainPlayer);

				players.AddUnique(mainPlayer);

				mainPlayer->AssignTeam_Implementation(team);

				TArray<AActor*> cameras;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARaiderCameraFollow::StaticClass(), cameras);
				for (AActor* cam : cameras)
				{
					ARaiderCameraFollow* myCamera = Cast<ARaiderCameraFollow>(cam);
					if (!myCamera->bIsUsed)
					{
						myCamera->NewPlayerJoin(controller, mainPlayer);
						break;
					}
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Main Player is null"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Players Start is Null"));
		}
	
	}
}


