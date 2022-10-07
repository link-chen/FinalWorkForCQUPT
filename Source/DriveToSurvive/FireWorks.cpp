// Fill out your copyright notice in the Description page of Project Settings.


#include "FireWorks.h"

// Sets default values
AFireWorks::AFireWorks()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TailComponent=CreateDefaultSubobject<UNiagaraComponent>(TEXT("Tail"));
	BoomComponent=CreateDefaultSubobject<UNiagaraComponent>(TEXT("Boom"));
}

// Called when the game starts or when spawned
void AFireWorks::BeginPlay()
{
	Super::BeginPlay();
	MaxHeight=MaxHeight+rand();
	TailComponent->Activate();
	BoomComponent->Deactivate();
}

// Called every frame
void AFireWorks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(GetActorLocation().Z>=MaxHeight)
	{
		TailComponent->Deactivate();
		BoomComponent->Activate();
	}
}

