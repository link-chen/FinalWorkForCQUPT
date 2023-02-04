// Fill out your copyright notice in the Description page of Project Settings.


#include "BoomEnemy.h"

void ABoomEnemy::Death()
{
	UE_LOG(LogTemp,Warning,TEXT("Boom"));
}

void ABoomEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABoomEnemy::BeginPlay()
{
	Super::BeginPlay();
	bLive=true;
}

void ABoomEnemy::GetHurt(float Value)
{
	UE_LOG(LogTemp,Warning,TEXT("BoomGetHurt"));
}

void ABoomEnemy::PlayDeathAnimation()
{
	Super::PlayDeathAnimation();
	Death();
}
