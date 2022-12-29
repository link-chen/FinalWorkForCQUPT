// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBullte.h"

// Sets default values
AGunBullte::AGunBullte()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AGunBullte::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AGunBullte::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

