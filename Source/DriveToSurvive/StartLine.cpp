// Fill out your copyright notice in the Description page of Project Settings.


#include "StartLine.h"

// Sets default values
AStartLine::AStartLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Line=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Line"));
}

// Called when the game starts or when spawned
void AStartLine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStartLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

