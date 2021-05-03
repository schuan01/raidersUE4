// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAttackType : uint8
{
    Attack1     UMETA(DisplayName = "Attack1"),
    Attack2      UMETA(DisplayName = "Attack2"),
    AttackSpecial   UMETA(DisplayName = "AttackSpecial"),
    None   UMETA(DisplayName = "None")
};