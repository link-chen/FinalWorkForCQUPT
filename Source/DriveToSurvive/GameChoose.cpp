// Fill out your copyright notice in the Description page of Project Settings.


#include "GameChoose.h"

#include "DTSSaveGame.h"
#include "TPSSaveGame.h"
#include "Kismet/GameplayStatics.h"

void AGameChoose::CheckFinish()
{
	if(GetFinish())
	{
		EnterTPSMode();
	}
	else
	{
		
	}
}

bool AGameChoose::GetFinish()
{
	if(UTPSSaveGame* Read=Cast<UTPSSaveGame>(UGameplayStatics::LoadGameFromSlot("TPSSaveSlot",1)))
	{
		UE_LOG(LogTemp,Warning,TEXT("%d"),Read->bFinishTPS);
		return Read->bFinishTPS;	
	}
	return false;
}
