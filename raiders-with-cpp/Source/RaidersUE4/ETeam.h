// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
    TeamA     UMETA(DisplayName = "TeamA"),
    TeamB     UMETA(DisplayName = "TeamB"),
    None     UMETA(DisplayName = "None")
};
