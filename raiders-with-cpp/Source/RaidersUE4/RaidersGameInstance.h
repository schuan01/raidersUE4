// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RaidersGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RAIDERSUE4_API URaidersGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	URaidersGameInstance();



public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatesVariables)
	bool bStateIs1VS1;

public:
	UFUNCTION(BlueprintCallable, Category = "State")
	void Change1VS1State(bool is1vs1);
	
};
