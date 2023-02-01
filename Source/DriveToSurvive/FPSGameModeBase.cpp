// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameModeBase.h"

#include "TPSSaveGame.h"
#include "Kismet/GameplayStatics.h"

void AFPSGameModeBase::SaveGameMessage()
{
	if(UTPSSaveGame* Save=Cast<UTPSSaveGame>(UGameplayStatics::CreateSaveGameObject(UTPSSaveGame::StaticClass())))
	{

		if(UGameplayStatics::SaveGameToSlot(Save,"SaveSlot",0))
		{
			
		}
	}
}

void AFPSGameModeBase::ReadGameMessage()
{
	
}

AFPSGameModeBase::AFPSGameModeBase()
{
	
}
