// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "RaidersBaseCharacter.h"
#include "RaidersBaseAltar.generated.h"

UCLASS()
class RAIDERSUE4_API ARaidersBaseAltar : public AActor
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	ARaidersBaseAltar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//----- MY ATTRIBUTES -----
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* mainMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* boxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* plane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AltarProperties)
		bool bCanWin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AltarProperties)
		bool bTempCanLevel;
	//---- END MY ATTRIBUTES -----
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "BoxCollision") 
	void OnOverlapBeginBoxCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION(BlueprintCallable, Category = "BoxCollision")
	void OnOverlapEndBoxCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



};
