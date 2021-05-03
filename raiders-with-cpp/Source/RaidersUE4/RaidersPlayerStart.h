// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "ETeam.h"
#include "RaidersPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class RAIDERSUE4_API ARaidersPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	ARaidersPlayerStart(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
		ETeam teamStart;
};
