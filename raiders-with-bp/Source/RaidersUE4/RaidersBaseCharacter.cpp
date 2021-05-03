// Fill out your copyright notice in the Description page of Project Settings.


#include "RaidersBaseCharacter.h"

// Sets default values
ARaidersBaseCharacter::ARaidersBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	baseLife = 3;
	baseArmor = 0.5f;
	baseDamage = 1;
	baseCritic = 1;

}

// Called when the game starts or when spawned
void ARaidersBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ARaidersBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
/*void ARaidersBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}*/

//-----------------RAIDERS FUNCTIONS -------------------------

float ARaidersBaseCharacter::ReceiveDamage(float originDamage, float originCriticProb)
{
	float damage = CalculateDamageFromOrigin(originDamage, originCriticProb);
	UE_LOG(LogTemp, Warning, TEXT("Final Damage to Target: %f"), damage);
	
	return damage;
	
}

/*
	Calculate the damage from origin, taking into account the Armor and the critic
	After calculating the damage, lets do the Damage direct to the Life
*/
float ARaidersBaseCharacter::CalculateDamageFromOrigin(float originDamage, float originCriticProb)
{
	//Multiply the origin damage by the critic
	float damage = originDamage * FMath::RoundHalfToZero(originCriticProb);//i.e 20 * 1.1
	
	//Get the Base armor of the target and reduce damage
	damage = damage - baseArmor;

	

	return damage;
	
}

void ARaidersBaseCharacter::DoFinalDamageToLife(float finalDamage)
{
	if (finalDamage > 0)
	{
		baseLife = baseLife - finalDamage;
	}

	
	UE_LOG(LogTemp, Warning, TEXT("Life remaining: %f"), baseLife);

}

void ARaidersBaseCharacter::KillCharacter()
{
	//Destroy();
}

void ARaidersBaseCharacter::AddLootToList(ARaiderBaseLoot* loot)
{

	listLoots.Add(loot);
}

void ARaidersBaseCharacter::RemoveAllLoot(bool dropLoot)
{
	if (!dropLoot)
	{
		listLoots.Empty();
	}
	else
	{
		//DROP ALL THE LOOT
	}
}


