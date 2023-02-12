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
	/*
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);
	for(AActor* Actor:Actors)
	{
		if(ABaseEnemy* Enemy=Cast<ABaseEnemy>(Actor))
			Enemies.Add(Enemy);
	}
	*/
	GetWorldTimerManager().SetTimer(Timer,this,&AFPSGameModeBase::CreateEnemy,5,true);
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
	UE_LOG(LogTemp,Warning,TEXT("ReStart"));
	if(APlayerCharater* GamePlayer=Cast<APlayerCharater>(NewPlayer->GetCharacter()))
	{
		UE_LOG(LogTemp,Warning,TEXT("Set"));
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

void AFPSGameModeBase::CreateEnemy()
{
	/*
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
		int RandPivote=0;
		int RandResult=rand()%EnemyTemplate.Num();
		RandPivote=RandResult<=EnemyTemplate.Num()-1?RandResult:0;
		ABaseEnemy* Enemy=GetWorld()->SpawnActor<ABaseEnemy>(EnemyTemplate[RandPivote],FVector(259120.0f,59830.0f,0.0f),FRotator(0.0f,0.0f,0.0f));
		Enemies.Add(Enemy);
	}
	*/
}
