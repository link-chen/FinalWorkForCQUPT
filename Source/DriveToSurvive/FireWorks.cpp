// Fill out your copyright notice in the Description page of Project Settings.


#include "FireWorks.h"

// Sets default values
AFireWorks::AFireWorks()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TailComponent=CreateDefaultSubobject<UNiagaraComponent>(TEXT("Tail"));
	BoomComponent=CreateDefaultSubobject<UNiagaraComponent>(TEXT("Boom"));
	BoomComponent->SetupAttachment(TailComponent);
}

// Called when the game starts or when spawned
void AFireWorks::BeginPlay()
{
	Super::BeginPlay();
	MaxHeight=MaxHeight+rand()%10;
	TailComponent->Activate();
	BoomComponent->Deactivate();
	bBoomed=false;
}

// Called every frame
void AFireWorks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset(FVector(0,0,2.75f));
	if(GetActorLocation().Z>=MaxHeight&&!bBoomed)
	{
		UE_LOG(LogTemp,Warning,TEXT("FireWorksBoom"));
		TailComponent->Deactivate();
		BoomComponent->Activate();
		bBoomed=true;
		Boom();
	}
}

