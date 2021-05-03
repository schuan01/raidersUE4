// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "RaidersMainPlayer.h"
#include "RaiderCameraFollow.generated.h"

UCLASS()
class RAIDERSUE4_API ARaiderCameraFollow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARaiderCameraFollow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* MainCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		ARaidersMainPlayer* PlayerToFollow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsUsed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector TargetPos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector PreviousPos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float InterpSpeed;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void UpdateCamera();

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void NewPlayerJoin(APlayerController* newPlayerController, ARaidersMainPlayer* playerSpawn );

};
