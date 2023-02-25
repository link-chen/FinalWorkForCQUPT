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
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);
	for(AActor* Actor:Actors)
	{
		if(ABaseEnemy* Enemy=Cast<ABaseEnemy>(Actor))
			Enemies.Add(Enemy);
		if(ABreakingPoint* BreakingPoint=Cast<ABreakingPoint>(Actor))
			BreakingPoints.Add(BreakingPoint);
	}

	GetWorldTimerManager().SetTimer(Timer,this,&AFPSGameModeBase::CheckBreakingPoint,1.0f,true,0);
}

AFPSGameModeBase::AFPSGameModeBase()
{
	if(Player!=nullptr)
	{
		DefaultPawnClass=Player;
	}
}

void AFPSGameModeBase::RestartPlayer(AController* NewPlayer,FVector CurrentLocation)
{
	Super::RestartPlayer(NewPlayer);
	if(APlayerCharater* GamePlayer=Cast<APlayerCharater>(NewPlayer->GetCharacter()))
	{
		GamePlayer->ShowUI();
		GamePlayer->SetActorLocation(CurrentLocation);
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

bool AFPSGameModeBase::CanCreateEnemy()
{
	int Left=0;
	for(int i=0;i<Enemies.Num();i++)
	{
		if(Enemies[i]!=nullptr)
		{
			Left++;
		}
	}
	if(Left<MaxEnemyNumber)
	{
		return true;
	}
	return false;

}

void AFPSGameModeBase::AddEnemy(ABaseEnemy* Enemy)
{
	if(Enemy)
	{
		for(int i=0;i<Enemies.Num();i++)
		{
			if(Enemies[i]==nullptr)
			{
				Enemies[i]=Enemy;
				return;
			}
		}
		Enemies.Add(Enemy);
	}
}

void AFPSGameModeBase::SpawnAirPlan()
{
	if(AirPlan)
	{
		AAirPlan* Air=GetWorld()->SpawnActor<AAirPlan>(AirPlan,AirPlanLocation,FRotator(0.0f));
		Air->SetActorScale3D(FVector(2.0f));
		Air->bEnter=true;
		Air->CPPStartFly();
	}
}

void AFPSGameModeBase::CheckBreakingPoint()
{
	int NullNum=0;
	for(ABreakingPoint* BreakingPoint:BreakingPoints)
		if(!BreakingPoint)
			NullNum++;
	if(NullNum==BreakingPoints.Num())
	{
		SpawnAirPlan();
		GetWorldTimerManager().ClearTimer(Timer);
		BreakPointClear();
	}
}

void AFPSGameModeBase::SetBreakingPoints(ABreakingPoint* BreakingPoint)
{
	for(int i=0;i<BreakingPoints.Num();i++)
		if(BreakingPoints[i]==BreakingPoint)
		{
			BreakingPoints[i]=nullptr;
		}
}
