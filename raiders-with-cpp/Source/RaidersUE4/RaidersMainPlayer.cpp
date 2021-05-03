// Fill out your copyright notice in the Description page of Project Settings.


#include "RaidersMainPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "RaidersPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "RaidersGameMode.h"
#include <RaidersUE4\RaidersPlayerStart.h>

ARaidersMainPlayer::ARaidersMainPlayer(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	eye_l = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this,TEXT("eye_l"));
	eye_l->SetupAttachment(GetMesh(), "joint_head");
	//eye_l->AttachTo(GetMesh(), "joint_head", EAttachLocation::SnapToTarget);
	eye_l->bEditableWhenInherited = true;
	eye_r = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this,TEXT("eye_r"));
	eye_r->SetupAttachment(GetMesh(), TEXT("joint_head"));
	eye_r->bEditableWhenInherited = true;
	mask = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this,TEXT("mask"));
	mask->SetupAttachment(GetMesh());
	mask->bEditableWhenInherited = true;
	weapon = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this,TEXT("weapon"));
	weapon-> SetupAttachment(GetMesh());
	weapon->bEditableWhenInherited = true;
	shield = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this,TEXT("shield"));
	shield->SetupAttachment(GetMesh());
	shield->bEditableWhenInherited = true;
	meshDropBossIndicator = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this,TEXT("dropBossIndicator"));
	meshDropBossIndicator->SetupAttachment(GetMesh());
	meshDropBossIndicator->bEditableWhenInherited = true;
	
	Clothes = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this,TEXT("Clothes"));
	Clothes->SetupAttachment(GetCapsuleComponent());
	warrior_armor_lvl1 = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this,TEXT("warrior_armor_lvl1"));
	warrior_armor_lvl1->SetupAttachment(Clothes);
	warrior_armor_lvl1->bEditableWhenInherited = true;
	warrior_armor_lvl2 = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this,TEXT("warrior_armor_lvl2"));
	warrior_armor_lvl2->SetupAttachment(Clothes);
	warrior_armor_lvl2->bEditableWhenInherited = true;
	warrior_armor_lvl3 = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this,TEXT("warrior_armor_lvl3"));
	warrior_armor_lvl3->SetupAttachment(Clothes);
	warrior_armor_lvl3->bEditableWhenInherited = true;
	tank_armor_lvl1 = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this,TEXT("tank_armor_lvl1"));
	tank_armor_lvl1->SetupAttachment(Clothes);
	tank_armor_lvl2 = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this,TEXT("tank_armor_lvl2"));
	tank_armor_lvl2->SetupAttachment(Clothes);
	tank_armor_lvl3 = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this,TEXT("tank_armor_lvl3"));
	tank_armor_lvl3->SetupAttachment(Clothes);
	mage_armor_lvl1 = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this,TEXT("mage_armor_lvl1"));
	mage_armor_lvl1->SetupAttachment(Clothes);
	mage_armor_lvl2 = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this,TEXT("mage_armor_lvl2"));
	mage_armor_lvl2->SetupAttachment(Clothes);
	mage_armor_lvl3 = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this,TEXT("mage_armor_lvl3"));
	mage_armor_lvl3->SetupAttachment(Clothes);
	hunter_armor_lvl1 = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this,TEXT("hunter_armor_lvl1"));
	hunter_armor_lvl1->SetupAttachment(Clothes);
	hunter_armor_lvl2 = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this,TEXT("hunter_armor_lvl2"));
	hunter_armor_lvl2->SetupAttachment(Clothes);
	hunter_armor_lvl3 = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this,TEXT("hunter_armor_lvl3"));
	hunter_armor_lvl3->SetupAttachment(Clothes);

	player_indicator_blue = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this,TEXT("player_indicator_blue"));
	player_indicator_blue->SetupAttachment(GetCapsuleComponent());
	player_indicator_blue->bEditableWhenInherited = true;
	player_indicator_red = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this,TEXT("player_indicator_red"));
	player_indicator_red->SetupAttachment(GetCapsuleComponent());
	player_indicator_red->bEditableWhenInherited = true;

	this->currentLevel = 0;
	this->bCanAttack = false;
	this->classType = EMaskType::None;
	this->team = ETeam::None;
	this->initLife = 0.0f;
	this->powerACoolDown = 5.0f;
	this->respawnDelay = 6.0f;
	this->bHasDropBoss = false;
	this->bCanPickUpDropBoss = true;
	this->initMaxWalkSpeed = 300.0f;
	
	//SET STATS LVL 1
	//MAGE
	this->mapPlayerLvl1Stats.Add(TEXT("Mage_Base_Armor"), 0.0f);
	this->mapPlayerLvl1Stats.Add(TEXT("Mage_Base_Life"), 3.0f);
	this->mapPlayerLvl1Stats.Add(TEXT("Mage_Base_Damage_Attack1"), 1.5f);
	this->mapPlayerLvl1Stats.Add(TEXT("Mage_Base_Damage_Attack2"), 1.5f);
	this->mapPlayerLvl1Stats.Add(TEXT("Mage_Base_Critic"), 1.0f);

	//WARRIOR
	this->mapPlayerLvl1Stats.Add(TEXT("Warrior_Base_Armor"), 0.0f);
	this->mapPlayerLvl1Stats.Add(TEXT("Warrior_Base_Life"), 3.0f);
	this->mapPlayerLvl1Stats.Add(TEXT("Warrior_Base_Damage_Attack1"), 1.0f);
	this->mapPlayerLvl1Stats.Add(TEXT("Warrior_Base_Damage_Attack2"), 2.0f);
	this->mapPlayerLvl1Stats.Add(TEXT("Warrior_Base_Critic"), 1.0f);

	//TANK
	this->mapPlayerLvl1Stats.Add(TEXT("Tank_Base_Armor"), 0.0f);
	this->mapPlayerLvl1Stats.Add(TEXT("Tank_Base_Life"), 3.0f);
	this->mapPlayerLvl1Stats.Add(TEXT("Tank_Base_Damage_Attack1"), 1.0f);
	this->mapPlayerLvl1Stats.Add(TEXT("Tank_Base_Damage_Attack2"), 1.0f);
	this->mapPlayerLvl1Stats.Add(TEXT("Tank_Base_Critic"), 1.0f);

	//HUNTER
	this->mapPlayerLvl1Stats.Add(TEXT("Hunter_Base_Armor"), 0.0f);
	this->mapPlayerLvl1Stats.Add(TEXT("Hunter_Base_Life"), 3.0f);
	this->mapPlayerLvl1Stats.Add(TEXT("Hunter_Base_Damage_Attack1"), 1.0f);
	this->mapPlayerLvl1Stats.Add(TEXT("Hunter_Base_Damage_Attack2"), 1.0f);
	this->mapPlayerLvl1Stats.Add(TEXT("Hunter_Base_Critic"), 1.0f);

	//SET STATS LVL 2
	//MAGE
	this->mapPlayerLvl2Stats.Add(TEXT("Mage_Base_Armor"), 0.0f);
	this->mapPlayerLvl2Stats.Add(TEXT("Mage_Base_Life"), 4.0f);
	this->mapPlayerLvl2Stats.Add(TEXT("Mage_Base_Damage_Attack1"), 1.5f);
	this->mapPlayerLvl2Stats.Add(TEXT("Mage_Base_Damage_Attack2"), 1.5f);
	this->mapPlayerLvl2Stats.Add(TEXT("Mage_Base_Critic"), 1.0f);

	//WARRIOR
	this->mapPlayerLvl2Stats.Add(TEXT("Warrior_Base_Armor"), 0.0f);
	this->mapPlayerLvl2Stats.Add(TEXT("Warrior_Base_Life"), 4.0f);
	this->mapPlayerLvl2Stats.Add(TEXT("Warrior_Base_Damage_Attack1"), 1.5f);
	this->mapPlayerLvl2Stats.Add(TEXT("Warrior_Base_Damage_Attack2"), 3.0f);
	this->mapPlayerLvl2Stats.Add(TEXT("Warrior_Base_Critic"), 1.0f);

	//TANK
	this->mapPlayerLvl2Stats.Add(TEXT("Tank_Base_Armor"), 0.0f);
	this->mapPlayerLvl2Stats.Add(TEXT("Tank_Base_Life"), 5.0f);
	this->mapPlayerLvl2Stats.Add(TEXT("Tank_Base_Damage_Attack1"), 2.0f);
	this->mapPlayerLvl2Stats.Add(TEXT("Tank_Base_Damage_Attack2"), 1.5f);
	this->mapPlayerLvl2Stats.Add(TEXT("Tank_Base_Critic"), 1.0f);

	//HUNTER
	this->mapPlayerLvl2Stats.Add(TEXT("Hunter_Base_Armor"), 0.0f);
	this->mapPlayerLvl2Stats.Add(TEXT("Hunter_Base_Life"), 4.0f);
	this->mapPlayerLvl2Stats.Add(TEXT("Hunter_Base_Damage_Attack1"), 1.5f);
	this->mapPlayerLvl2Stats.Add(TEXT("Hunter_Base_Damage_Attack2"), 1.5f);
	this->mapPlayerLvl2Stats.Add(TEXT("Hunter_Base_Critic"), 1.0f);

	//SET STATS LVL 3
	//MAGE
	this->mapPlayerLvl3Stats.Add(TEXT("Mage_Base_Armor"), 0.0f);
	this->mapPlayerLvl3Stats.Add(TEXT("Mage_Base_Life"), 5.0f);
	this->mapPlayerLvl3Stats.Add(TEXT("Mage_Base_Damage_Attack1"), 1.5f);
	this->mapPlayerLvl3Stats.Add(TEXT("Mage_Base_Damage_Attack2"), 1.5f);
	this->mapPlayerLvl3Stats.Add(TEXT("Mage_Base_Critic"), 1.0f);

	//WARRIOR
	this->mapPlayerLvl3Stats.Add(TEXT("Warrior_Base_Armor"), 0.0f);
	this->mapPlayerLvl3Stats.Add(TEXT("Warrior_Base_Life"), 5.0f);
	this->mapPlayerLvl3Stats.Add(TEXT("Warrior_Base_Damage_Attack1"), 2.0f);
	this->mapPlayerLvl3Stats.Add(TEXT("Warrior_Base_Damage_Attack2"), 4.0f);
	this->mapPlayerLvl3Stats.Add(TEXT("Warrior_Base_Critic"), 1.0f);

	//TANK
	this->mapPlayerLvl3Stats.Add(TEXT("Tank_Base_Armor"), 0.0f);
	this->mapPlayerLvl3Stats.Add(TEXT("Tank_Base_Life"), 7.0f);
	this->mapPlayerLvl3Stats.Add(TEXT("Tank_Base_Damage_Attack1"), 3.0f);
	this->mapPlayerLvl3Stats.Add(TEXT("Tank_Base_Damage_Attack2"), 2.0f);
	this->mapPlayerLvl3Stats.Add(TEXT("Tank_Base_Critic"), 1.0f);

	//HUNTER
	this->mapPlayerLvl3Stats.Add(TEXT("Hunter_Base_Armor"), 0.0f);
	this->mapPlayerLvl3Stats.Add(TEXT("Hunter_Base_Life"), 5.0f);
	this->mapPlayerLvl3Stats.Add(TEXT("Hunter_Base_Damage_Attack1"), 3.0f);
	this->mapPlayerLvl3Stats.Add(TEXT("Hunter_Base_Damage_Attack2"), 2.0f);
	this->mapPlayerLvl3Stats.Add(TEXT("Hunter_Base_Critic"), 1.0f);
	

	
}

void ARaidersMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	this->bCanAttack = false;
	this->initLife = baseLife;
	

	//TODO DELAY .2


	//this->maskInitLocation = this->mask->GetRelativeLocation();
	//this->maskInitScale = this->mask->GetRelativeScale3D();

	//this->initMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	
}

void ARaidersMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//TODO
	//Cast<ARaidersPlayerController>(GetController()->GetPawn())->SetAudioListenerOverride(GetMesh(),FVector::ZeroVector,FRotator::ZeroRotator);
}

void ARaidersMainPlayer::TriggerDeath_Implementation()
{

	this->bIsDead = true;
	this->GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	this->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle,ECollisionResponse::ECR_Overlap);
	this->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

	//Disable Input
	this->GetController()->DisableInput(Cast<ARaidersPlayerController>(GetController()));

	//Disable all propierties
	bCanAttack = false;
	bIsAttacking_1 = false;
	bIsAttacking_2 = false;
	bIsAttacking_Special = false;
	bCanPickUpLoot = false;

	//Remove Tags for IA
	this->Tags.Empty();

	//DROP BOSS ITEM IF ABLE
	if (bHasDropBoss)
	{
		DropBossItem();
	}

	DropItems();

	//Notify BP for UI stuff
	OnTriggerDeath();

	//trigger respawn Player after delay
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &ARaidersMainPlayer::RespawnPlayer, respawnDelay, true);

}

void ARaidersMainPlayer::ToggleWeaponCollision_Implementation(bool bIsActive)
{
	Super::ToggleWeaponCollision_Implementation(bIsActive);
	this->weapon->SetGenerateOverlapEvents(bIsActive);
}

void ARaidersMainPlayer::DropBossItem_Implementation()
{
	meshDropBossIndicator->SetVisibility(false);
	bCanPickUpDropBoss = false;
	bHasDropBoss = false;
	FVector location = this->GetActorLocation();
	FRotator rotator = FRotator(0, 0, 0);
	FVector scale = FVector(1, 1, 1);
	FTransform transform = FTransform(rotator, location, scale);
	FActorSpawnParameters params;

	GetWorld()->SpawnActor(ToSpawnBossDrop, &transform,params);
	GetCharacterMovement()->MaxWalkSpeed = initMaxWalkSpeed;

	//TODO PARTICLE
}

void ARaidersMainPlayer::PickUpBossDrop_Implementation()
{
	this->bHasDropBoss = true;
	this->meshDropBossIndicator->SetVisibility(true);
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed - 100;
	
	//TODO PARTICLE
}

void ARaidersMainPlayer::DropItems()
{
	FVector spawnLoc = GetActorLocation();
	
	
	if (this->listLoots.Num() > 0)
	{
		//SHUFLLE FIRST
		uint8 LastIndex = this->listLoots.Num() - 1;
		for (uint8 i = 0; i <= LastIndex; ++i)
		{
			uint8 Index = FMath::RandRange(i, LastIndex);
			if (i != Index)
			{
				this->listLoots.Swap(i, Index);
			}
		}

		uint8 half = this->listLoots.Num() / 2;

		for (uint8 i = 0; i < half; i++)
		{
			FVector* tempLoc = new FVector(FMath::RandRange(-20.0f,50.0f), FMath::RandRange(-20.0f, 50.0f), FMath::RandRange(1.0f, 20.0f));
			spawnLoc = spawnLoc + *tempLoc;

			FRotator rotator = FRotator(0, 0, 0);
			FVector scale = FVector(1, 1, 1);

			FTransform transform = FTransform(rotator, spawnLoc, scale);
			FActorSpawnParameters params;

			GetWorld()->SpawnActor(this->listLoots[i]->GetClass(), &transform, params);
			this->listLoots.RemoveAt(i);
		}
	}


}

void ARaidersMainPlayer::RespawnPlayer_Implementation()
{
	this->bIsDead = false;
	ARaidersGameMode* gameMode = Cast<ARaidersGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	TArray<ARaidersPlayerStart*> starts;
	for (AActor* playerStart : gameMode->allPlayersStartArray)
	{
		ARaidersPlayerStart* start = Cast<ARaidersPlayerStart>(playerStart);
		if (start->teamStart == this->team)
		{
			starts.Add(start);
		}
	}

	int32 rand = FMath::RandRange(0, starts.Num() - 1);

	this->SetActorLocation(starts[rand]->GetActorLocation());

	this->initLife = this->baseLife;

	//TODO UPDATE LIFE
}

void ARaidersMainPlayer::AssignTeam_Implementation(ETeam pTeam)
{
	this->team = pTeam;
	switch (this->team)
	{
	case ETeam::TeamA:
		this->player_indicator_blue->SetVisibility(true);
		this->player_indicator_red->SetVisibility(false);
		break;
	case ETeam::TeamB:
		this->player_indicator_blue->SetVisibility(false);
		this->player_indicator_red->SetVisibility(true);
		break;
	default:
		this->player_indicator_blue->SetVisibility(true);
		this->player_indicator_red->SetVisibility(false);
		break;
	}
}

void ARaidersMainPlayer::ChooseClass_Implementation(EMaskType pTypeClass)
{
	if (this->currentLevel == 0)
	{
		this->currentLevel = 1;
	}

	this->bCanAttack = true;

	this->classType = pTypeClass;

	this->UpgradeArmor_Implementation(this->classType);

	switch (this->currentLevel)
	{
	case 1:
		this->SetNextStats_Implementation(this->mapPlayerLvl1Stats);
		break;
	case 2:
		this->SetNextStats_Implementation(this->mapPlayerLvl2Stats);
		break;
	case 3:
		this->SetNextStats_Implementation(this->mapPlayerLvl3Stats);
		break;
	default:
		break;
	}

	//NOTIFY BP
	OnChooseClass();

}

void ARaidersMainPlayer::UpdateStaticMeshLvlUpgrade_Implementation(EMaskType pTypeClass, TMap<FString, UStaticMesh*> &mapArmor)
{
	
}

void ARaidersMainPlayer::UpdateSkeletalMeshLvlUpgrade_Implementation(EMaskType pTypeClass, TMap<FString, UStaticMesh*> &mapArmor)
{
	//FIRST HIDE ALL MESHES BUT NOT THE ARMOR. THE ARMOR ALREADY HAS A NEW LEVEL
	TArray<USceneComponent*> arrayChildren;
	this->Clothes->GetChildrenComponents(false,arrayChildren);

	FString className = UEnum::GetValueAsString<EMaskType>(this->classType);
	FString armorType;
	switch (pTypeClass) 
	{
		case EMaskType::Warrior:
			armorType = "warrior";
			break;
		case EMaskType::Hunter:
			armorType = "hunter";
			break;
		case EMaskType::Mage:
			armorType = "mage";
			break;
		case EMaskType::Tank:
			armorType = "tank";
			break;
	}


	FString armorMeshName = armorType.ToLower() + TEXT("_") + TEXT("armor") + TEXT("_lvl") + FString::FromInt(this->currentLevel);

	for (USceneComponent* comp : arrayChildren) 
	{
		USkeletalMeshComponent* skel = Cast<USkeletalMeshComponent>(comp);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *skel->GetName());
		if (skel->GetName() == armorMeshName)
		{
			
			skel->SetVisibility(true);
		}
		else
		{
			skel->SetVisibility(false);
		}
	}

	UpdateStaticMeshLvlUpgrade_Implementation(pTypeClass,mapArmor);

	//NOW RELOCATE SPECIAL OFFSETS FOR THE REST OF THE PARTS

	this->mask->SetRelativeScale3D(this -> maskInitScale);
	this->mask->SetRelativeLocation(this->maskInitLocation);
	FString maskName;
	switch (pTypeClass)
	{
	case EMaskType::Warrior:
			this->mask->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("socketOffsetMask"));
			maskName = this->mask->GetStaticMesh()->GetName();
			if (maskName.Contains(TEXT("lvl3")))
			{
				FVector* offsetLoc = new FVector(2, 0, 0);
				this->mask->SetRelativeLocation(this->mask->GetRelativeLocation() + *offsetLoc);

				FVector* offsetRot = new FVector(0.1, 0.1, 0.1);
				this->mask->SetRelativeScale3D(this->mask->GetRelativeScale3D() + *offsetRot);
			}

			if (maskName.Contains(TEXT("lvl2")))
			{
				
				FVector* offsetRot = new FVector(0.1, 0.1, 0.1);
				this->mask->SetRelativeScale3D(this->mask->GetRelativeScale3D() + *offsetRot);
			}

			if (maskName.Contains(TEXT("lvl1")))
			{

				FVector* offsetRot = new FVector(0.1, 0.1, 0.1);
				this->mask->SetRelativeScale3D(this->mask->GetRelativeScale3D() + *offsetRot);
			}
		break;
	case EMaskType::Mage:
		//TODO
		break;
	case EMaskType::Tank:
		//TODO
		break;
	case EMaskType::Hunter:
		//TODO
		break;
	case EMaskType::None:
		break;
	default:
		break;
	}

}

void ARaidersMainPlayer::UpgradeArmor_Implementation(EMaskType pTypeClass)
{
	switch (pTypeClass)
	{
	case EMaskType::Warrior:
		this->UpdateSkeletalMeshLvlUpgrade_Implementation(pTypeClass,this->mapWarriorArmor);
		break;
	case EMaskType::Mage:
		this->UpdateSkeletalMeshLvlUpgrade_Implementation(pTypeClass, this->mapMageArmor);
		break;
	case EMaskType::Tank:
		this->UpdateSkeletalMeshLvlUpgrade_Implementation(pTypeClass, this->mapTankArmor);
		break;
	case EMaskType::Hunter:
		this->UpdateSkeletalMeshLvlUpgrade_Implementation(pTypeClass, this->mapHunterArmor);
		break;
	case EMaskType::None:
		break;
	default:
		break;
	}
}

void ARaidersMainPlayer::SetNextStats_Implementation(TMap<FString, float> &newStats)
{
	FString name = UEnum::GetValueAsString<EMaskType>(this->classType);
	TMap<FString, float> tempKeyClass;

	//FILTER ONLY THE NAME WITH THE CLASS
	for (TPair<FString, float>& Kvp : newStats)
	{
		if (Kvp.Key.Contains(name))
		{
			tempKeyClass.Add(Kvp.Key, Kvp.Value);
		}
		
	}

	for (TPair<FString, float>& KvpTemp : tempKeyClass)
	{
		if (KvpTemp.Key.Contains(TEXT("Life")))
		{
			this->baseLife = KvpTemp.Value;
			this->initLife = KvpTemp.Value;
		}

		if (KvpTemp.Key.Contains(TEXT("Attack1")))
		{
			this->baseDamage1 = KvpTemp.Value;
		}

		if (KvpTemp.Key.Contains(TEXT("Attack2")))
		{
			this->baseDamage2 = KvpTemp.Value;
		}

		if (KvpTemp.Key.Contains(TEXT("Armor")))
		{
			this->baseArmor = KvpTemp.Value;
		}

		if (KvpTemp.Key.Contains(TEXT("Critic")))
		{
			this->baseCritic = KvpTemp.Value;
		}

	}




}


