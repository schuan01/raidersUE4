// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RaiderBaseLoot.h"
#include "EAttackType.h"
#include "Components/CapsuleComponent.h"
#include "RaidersBaseCharacter.generated.h"


UCLASS()
class RAIDERSUE4_API ARaidersBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARaidersBaseCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//RAIDERS STATS

	//Initial Life
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RaiderStats)
	float baseLife;

	//Initial Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RaiderStats)
	float baseDamage1;

	//Initial Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RaiderStats)
	float baseDamage2;

	//Initial Armor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RaiderStats)
	float baseArmor;

	//Critic Multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RaiderStats)
	float baseCritic;

	//----- LOOT -----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RaiderLoot)
	TArray<ARaiderBaseLoot*> listLoots;

	//---- CharacterState

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterState)
	bool bIsAttacking_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterState)
	bool bIsAttacking_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterState)
	bool bIsAttacking_Special;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterState)
	bool bIsDead;

	//---- Sounds

	UPROPERTY(EditAnywhere, Category = Sounds) 
	class USoundBase* deathSound;

	UPROPERTY(EditAnywhere, Category = Sounds)
	class USoundBase* hitSound;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	//-----------RAIDER FUNCTIONS-------------------
	
	//Calculate the damage from origin, taking into account the Armor and the critic
	//After calculating the damage, lets do the Damage direct to the Life
	UFUNCTION(BlueprintCallable, Category = "Damage")
	float CalculateDamageFromOrigin(float originDamage,float originCriticProb);

	//Do Final damage to target
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void DoFinalDamageToLife(float finalDamage);

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void KillCharacter();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	float ReceiveDamage(float originDamage, float originCriticProb);

	UFUNCTION(BlueprintCallable, Category = "Loot")
	void AddLootToList(ARaiderBaseLoot* loot);

	UFUNCTION(BlueprintCallable, Category = "Loot")
	void RemoveAllLoot(bool bDropLoot);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Collision")
	void ToggleWeaponCollision(bool bIsActive);
	virtual void ToggleWeaponCollision_Implementation(bool bIsActive);

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ReceiveDamageBP();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void SendDamageToTarget(class ARaidersBaseCharacter *CharacterDestination,float baseDamageAttack1, float baseDamageAttack2,EAttackType attackType  );

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Death")
	void TriggerDeath();
	virtual void TriggerDeath_Implementation();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateDamageReceivedUI(float Damage, float BaseLifeBeforeDamage);

	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayHurtSound(class USoundBase* hurt);

	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayDeathSound(class USoundBase* death);

	UFUNCTION(BlueprintCallable, Category = "Drop")
	virtual void DropItems();
};
