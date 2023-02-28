// Fill out your copyright notice in the Description page of Project Settings.


#include "GameChoose.h"

#include "DTSSaveGame.h"
#include "TPSSaveGame.h"
#include "Kismet/GameplayStatics.h"

bool AGameChoose::GetFinish()
{
	if(UTPSSaveGame* Save=Cast<UTPSSaveGame>(UGameplayStatics::CreateSaveGameObject(UDTSSaveGame::StaticClass())))
	{
		return Save->bFinishTPS;	
	}
	return false;
}
