// Fill out your copyright notice in the Description page of Project Settings.


#include "BoomEnemy.h"

void ABoomEnemy::Death()
{
	UE_LOG(LogTemp,Warning,TEXT("BoomDeath"));
	GetWorldTimerManager().SetTimer(DeleteHandle,this,&ABoomEnemy::DieOut,DeleteTime,false);
}

void ABoomEnemy::Tick(float DeltaSeconds)
{
	//live check has done in baseenemy
	Super::Tick(DeltaSeconds);
}

void ABoomEnemy::BeginPlay()
{
	//All Init has done in baseenemy
	Super::BeginPlay();
}

void ABoomEnemy::GetHurt(float Value)
{
	//hurt has done in baseenemy
	Super::GetHurt(Value);
}

void ABoomEnemy::PlayDeathAnimation()
{
	Super::PlayDeathAnimation();
	Death();
}

void ABoomEnemy::DieOut()
{
	UE_LOG(LogTemp,Warning,TEXT("BoomEnemyBoom!"));
	ABomb* Bomb=GetWorld()->SpawnActor<ABomb>(BombClass,GetActorLocation(),GetActorRotation());
	Bomb->SetBoomValue(HurtValue);
	GetWorldTimerManager().ClearTimer(DeleteHandle);
	Destroy();
}
