// Fill out your copyright notice in the Description page of Project Settings.


#include "DRSTest.h"

#include "BaseCar.h"

// Sets default values
ADRSTest::ADRSTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box=CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	FScriptDelegate Del;
	Del.BindUFunction(this,"OnOverlayBegin");
	Box->OnComponentBeginOverlap.Add(Del);
}

// Called when the game starts or when spawned
void ADRSTest::BeginPlay()
{
	Super::BeginPlay();
	TimeSecond=0.0f;
}

// Called every frame
void ADRSTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADRSTest::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ABaseCar* Car=Cast<ABaseCar>(OtherActor))
	{
		float CurrentTime=GetGameTimeSinceCreation();
		float DeltaTime=CurrentTime-TimeSecond;
		TimeSecond=CurrentTime;
		if(DeltaTime<=1.0f)
		{
			Car->bCanUseDRS=true;
		}
	}
}

