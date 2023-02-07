// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameModeBase.h"

#include "TPSSaveGame.h"
#include "Kismet/GameplayStatics.h"

void AFPSGameModeBase::SaveGameMessage()
{
	if(UTPSSaveGame* Save=Cast<UTPSSaveGame>(UGameplayStatics::CreateSaveGameObject(UTPSSaveGame::StaticClass())))
	{

		if(UGameplayStatics::SaveGameToSlot(Save,"TPSSaveSlot",1))
		{
			
		}
	}
}

void AFPSGameModeBase::ReadGameMessage()
{
	
}

void AFPSGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	if (!OnPlayerDied.IsBound())
	{
		OnPlayerDied.AddDynamic(this, &AFPSGameModeBase::PlayerDied);
	}
}

AFPSGameModeBase::AFPSGameModeBase()
{
	if(Player!=nullptr)
	{
		DefaultPawnClass=Player;
	}
}

void AFPSGameModeBase::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);
	UE_LOG(LogTemp,Warning,TEXT("ReStart"));
	if(APlayerCharater* GamePlayer=Cast<APlayerCharater>(NewPlayer))
	{
		
	}
}

void AFPSGameModeBase::PlayerDied(ACharacter* Character)
{
	AController* CharacterController = Character->GetController();
}

void AFPSGameModeBase::BossCreate()
{
	UE_LOG(LogTemp,Warning,TEXT("SpawnBoss"));
}
