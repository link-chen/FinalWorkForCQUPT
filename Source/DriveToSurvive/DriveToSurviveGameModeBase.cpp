// Copyright Epic Games, Inc. All Rights Reserved.


#include "DriveToSurviveGameModeBase.h"

#include "BaseCar.h"
#include "DTSSaveGame.h"
#include "WheeledVehicleMovementComponent.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"

class ABaseCar;

ADriveToSurviveGameModeBase::ADriveToSurviveGameModeBase()
{
	LeftTime=5;
	Point=18;
}
void ADriveToSurviveGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("LightCount"));
	bCanCarRun=false;
	GetWorldTimerManager().SetTimer(Time,this,&ADriveToSurviveGameModeBase::CountTime,1,true);
	PlayerCar=Cast<ABaseCar>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(PlayerCar!=nullptr)
	ReadGameMessage();
	UE_LOG(LogTemp,Warning,TEXT("ERSRate==%f"),PlayerCar->GetERSRate());
	UE_LOG(LogTemp,Warning,TEXT("DownForceRate==%f"),PlayerCar->GetDownForceRate());
	UE_LOG(LogTemp,Warning,TEXT("ElectronicPower==%f"),PlayerCar->MaxElectronicPower);
	UE_LOG(LogTemp,Warning,TEXT("Mass==%f"),PlayerCar->GetVehicleMovementComponent()->Mass);
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
		Save->MaxElectronicPower=PlayerCar->ElectronicPower;
		Save->ERSRate=PlayerCar->GetERSRate();
		Save->Mass=PlayerCar->GetVehicleMovementComponent()->Mass;
		Save->Point=Point;
		Save->DownForceRate=PlayerCar->GetDownForceRate();
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
		Point=Read->Point;
		PlayerCar->MaxElectronicPower=Read->MaxElectronicPower;
		PlayerCar->SetERSRate(Read->ERSRate);
		PlayerCar->GetVehicleMovementComponent()->Mass=Read->Mass;
		PlayerCar->SetDownForceRate(Read->DownForceRate);
	}
}
