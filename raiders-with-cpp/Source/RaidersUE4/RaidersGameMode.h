// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RaidersGameInstance.h"
#include "RaidersMainPlayer.h"
#include "RaidersGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RAIDERSUE4_API ARaidersGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARaidersGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameType)
	bool bIs1vs1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Players)
	uint8 maxPlayerCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Players)
	TArray<AActor*>  allPlayersStartArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Players)
	TArray<APlayerController*>  playersController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Players)
	TArray<ARaidersMainPlayer*>  players;

	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
	TSubclassOf<ARaidersMainPlayer> RaiderMainPlayerBP;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Players")
	void SpawnCharacter(APlayerController* controller, ETeam team);
	void SpawnCharacter_Implementation(APlayerController* controller, ETeam team);
};
