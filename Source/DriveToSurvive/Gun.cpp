// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include <GeomUtils/GuContactBuffer.h>

#include "Components/AudioComponent.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(RootComponent);
	Audio=CreateDefaultSubobject<UAudioComponent>(TEXT("AudiComponent"));
	Audio->SetupAttachment(GunMesh);
	FireMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FireMesh"));
	FireMesh->SetupAttachment(GunMesh);
	LeftBullteMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("抛弹壳区域"));
	LeftBullteMesh->SetupAttachment(GunMesh);
	GunFireNiagaraComponent=CreateDefaultSubobject<UNiagaraComponent>(TEXT("GunFire"));
	GunFireNiagaraComponent->SetupAttachment(FireMesh);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	GunBullte=MaxBullte;

	GunMesh->AddForce(GunMesh->GetForwardVector()*100000.0f);

	bCanUse=true;
}

void AGun::Fire()
{
	UWorld* World=GetWorld();
	if(World)
	{
		if(GunBullte&&bCanUse)
		{
			UE_LOG(LogTemp,Warning,TEXT("GunFire"));
			World->SpawnActor<AGunBullte>(Bullte,GetFireLocation(),GetFireRotator());
			Audio->Play();
		}
	}
}

float AGun::GetShotTime()
{
	return ShotTime;
}

void AGun::ReLoadBullte()
{
	if(LeftGunBullte>=MaxBullte)
	{
		if(GunBullte!=0)
			LeftGunBullte-=(MaxBullte-GunBullte);	
		else
			LeftGunBullte-=MaxBullte;
		GunBullte=MaxBullte;
	}
	else
	{
		if(LeftGunBullte+GunBullte<=MaxBullte)
		{
			GunBullte+=LeftGunBullte;
			LeftGunBullte=0;
		}
		else
		{
			LeftGunBullte=(GunBullte+LeftGunBullte)-MaxBullte;
			GunBullte=MaxBullte;
		}
	}
}

void AGun::GiveUp()
{
	GunMesh->AddForce(FVector(10.0f,10.0f,10.0f));
}

FVector AGun::GetFireLocation()
{
	return FireMesh->GetComponentLocation();
}

FRotator AGun::GetFireRotator()
{
	return FireMesh->GetComponentRotation();
}

void AGun::UseBullte()
{
	
}


// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

