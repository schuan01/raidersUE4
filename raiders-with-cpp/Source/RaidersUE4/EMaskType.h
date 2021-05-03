// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMaskType : uint8
{
    Warrior     UMETA(DisplayName = "Warrior"),
    Mage      UMETA(DisplayName = "Mage"),
    Tank   UMETA(DisplayName = "Tank"),
    Hunter   UMETA(DisplayName = "Hunter"),
    None   UMETA(DisplayName = "None")
};
