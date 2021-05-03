// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RaidersBaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EMaskType.h"
#include "ETeam.h"
#include "EAttackType.h"
#include "RaidersPlayerController.h"
#include "RaiderBaseLoot.h"
#include "RaidersMainPlayer.generated.h"

/**
 * 
 */
UCLASS()
class RAIDERSUE4_API ARaidersMainPlayer : public ARaidersBaseCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* eye_r;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* eye_l;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* mask;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* weapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* shield;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* meshDropBossIndicator;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USceneComponent* Clothes;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* warrior_armor_lvl1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* warrior_armor_lvl2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* warrior_armor_lvl3;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* tank_armor_lvl1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* tank_armor_lvl2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* tank_armor_lvl3;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* mage_armor_lvl1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* mage_armor_lvl2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* mage_armor_lvl3;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* hunter_armor_lvl1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* hunter_armor_lvl2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* hunter_armor_lvl3;

	//INDICATORS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* player_indicator_blue;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* player_indicator_red;
	
public:
	// Sets default values for this character's properties
	ARaidersMainPlayer(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
	uint8 currentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
	bool bCanAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
	EMaskType classType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
	ETeam team;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
	float initLife;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoolDowns)
	float powerACoolDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Delays)
	float respawnDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Loot)
	bool bHasDropBoss;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Loot)
	bool bCanPickUpDropBoss;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Loot)
	bool bCanPickUpLoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUP)
	bool bCanLevelUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Vectors)
	FVector maskInitScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Vectors)
	FVector maskInitLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
	EAttackType currentAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
	float initMaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UILevelUP)
	uint8 amoutLevelUp2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UILevelUP)
	uint8 amoutLevelUp3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InitialStats)
	TMap<FString, float> mapPlayerLvl1Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InitialStats)
	TMap<FString, float> mapPlayerLvl2Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InitialStats)
	TMap<FString, float> mapPlayerLvl3Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ArmorLevelUp)
	TMap<FString, UStaticMesh*> mapMageArmor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ArmorLevelUp)
	TMap<FString, UStaticMesh*> mapWarriorArmor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ArmorLevelUp)
	TMap<FString, UStaticMesh*> mapTankArmor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ArmorLevelUp)
	TMap<FString, UStaticMesh*> mapHunterArmor;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Indicator)
	TSubclassOf<class ARaiderBaseLoot> ToSpawnBossDrop;

	//COMPONENTS FOR BP - MESHES
	

	//timer
	FTimerHandle timerHandle;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void TriggerDeath_Implementation() override;
	virtual void ToggleWeaponCollision_Implementation(bool bIsActive) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Drops")
	void DropBossItem();
	void DropBossItem_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Drops")
	void PickUpBossDrop();
	void PickUpBossDrop_Implementation();

	
	void DropItems() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Respawn")
	void RespawnPlayer();
	void RespawnPlayer_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Team")
	void AssignTeam(ETeam pTeam);
	void AssignTeam_Implementation(ETeam pTeam);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Class")
	void ChooseClass(EMaskType pTypeClass);
	void ChooseClass_Implementation(EMaskType pTypeClass);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Class")
	void UpdateSkeletalMeshLvlUpgrade(EMaskType pTypeClass, TMap<FString, UStaticMesh*> &mapArmor);
	void UpdateSkeletalMeshLvlUpgrade_Implementation(EMaskType pTypeClass, TMap<FString, UStaticMesh*> &mapArmor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Class")
    void UpdateStaticMeshLvlUpgrade(EMaskType pTypeClass, TMap<FString, UStaticMesh*> &mapArmor);
	void UpdateStaticMeshLvlUpgrade_Implementation(EMaskType pTypeClass, TMap<FString, UStaticMesh*> &mapArmor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Class")
	void UpgradeArmor(EMaskType pTypeClass);
	void UpgradeArmor_Implementation(EMaskType pTypeClass);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Stats")
	void SetNextStats(TMap<FString,float> &newStats);
	void SetNextStats_Implementation(TMap<FString, float> &newStats);


	//BP EVENTS

	//Event to notify BP after Trigger Death
	UFUNCTION(BlueprintImplementableEvent, Category = "Death")
	void OnTriggerDeath();

	UFUNCTION(BlueprintImplementableEvent, Category = "Class")
	void OnChooseClass();

	UFUNCTION(BlueprintImplementableEvent, Category = "Collision")
	void OnToggleWeaponCollision();

};
