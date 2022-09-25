// Copyright Epic Games, Inc. All Rights Reserved.


#include "DriveToSurviveGameModeBase.h"

#include "BaseCar.h"
#include "DTSSaveGame.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"

class ABaseCar;

ADriveToSurviveGameModeBase::ADriveToSurviveGameModeBase()
{
	LeftTime=5;
	Money=10000;
}
void ADriveToSurviveGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("LightCount"));
	bCanCarRun=false;
	GetWorldTimerManager().SetTimer(Time,this,&ADriveToSurviveGameModeBase::CountTime,1,true);
	PlayerCar=Cast<ABaseCar>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(PlayerCar!=nullptr)
		UE_LOG(LogTemp,Warning,TEXT("Player Is Not NULL"));
	ReadGameMessage();
}
void ADriveToSurviveGameModeBase::CountTime()
{
	if(LeftTime!=0)
		LeftTime--;
	else
	{
		bCanCarRun=true;
		GetWorldTimerManager().ClearTimer(Time);
	}
}
bool ADriveToSurviveGameModeBase::GetCarRunable()
{
	return bCanCarRun;
}

void ADriveToSurviveGameModeBase::SaveGameMessage()
{
	if(UDTSSaveGame* Save=Cast<UDTSSaveGame>(UGameplayStatics::CreateSaveGameObject(UDTSSaveGame::StaticClass())))
	{
		Save->FinishedCircle=FinishedCircle;
		if(UGameplayStatics::SaveGameToSlot(Save,"SaveSlot",0))
		{
			
		}
	}
}

void ADriveToSurviveGameModeBase::ReadGameMessage()
{
	if(UDTSSaveGame* Read=Cast<UDTSSaveGame>(UGameplayStatics::LoadGameFromSlot("SaveSlot",0)))
	{
		FinishedCircle=Read->FinishedCircle;
		Money=Read->Money;
	}
}
