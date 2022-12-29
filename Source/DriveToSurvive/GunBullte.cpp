// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBullte.h"

// Sets default values
AGunBullte::AGunBullte()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

// Called when the game starts or when spawned
void AGunBullte::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate Del;
	Del.BindUFunction(this,"NotifyHit");
	Mesh->OnComponentHit.Add(Del);
}

void AGunBullte::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp,Warning,TEXT("HitOn"));
}


// Called every frame
void AGunBullte::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

