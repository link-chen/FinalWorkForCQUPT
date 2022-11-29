// Fill out your copyright notice in the Description page of Project Settings.


#include "Clock.h"

#include <ThirdParty/openexr/Deploy/OpenEXR-2.3.0/OpenEXR/include/ImathMath.h>

// Sets default values
AClock::AClock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Time=0.0f;
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

void AClock::Count()
{
	Time+=0.2f;
}

float AClock::GetDayTime()
{
	return DayTime;
}

float AClock::GetLightForce()
{
	return 1.0f+sin(Time);
}




