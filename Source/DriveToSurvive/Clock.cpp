// Fill out your copyright notice in the Description page of Project Settings.


#include "Clock.h"

#include "Components/LightComponent.h"
#include "Engine/DirectionalLight.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AClock::AClock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AClock::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(Timer,this,&AClock::Count,TimePerSecond,true);
}

// Called every frame
void AClock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AClock::ReturnNum()
{
	return sin(RotateNum/57.29578)+1.0075f;
}


void AClock::Count()
{
	RotateNum+=Speed;
	Signal();
}




