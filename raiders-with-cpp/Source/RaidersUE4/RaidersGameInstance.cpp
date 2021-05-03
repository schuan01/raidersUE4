// Fill out your copyright notice in the Description page of Project Settings.


#include "RaidersGameInstance.h"

URaidersGameInstance::URaidersGameInstance()
{
	this->bStateIs1VS1 = false;
}


void URaidersGameInstance::Change1VS1State(bool is1vs1)
{
	this->bStateIs1VS1 = is1vs1;
}
