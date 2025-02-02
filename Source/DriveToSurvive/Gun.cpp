// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "DrawDebugHelpers.h"
#include <GeomUtils/GuContactBuffer.h>

#include "BaseCar.h"
#include "BaseEnemy.h"
#include "BoomEnemy.h"
#include "StartLine.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

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

void AGun::ReLoadAllBullte()
{
	GunBullte=MaxBullte;
	LeftGunBullte=MaxLeftBullte;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	GunBullte=MaxBullte;
	LeftGunBullte=MaxLeftBullte;

	Audio->Deactivate();
	GunFireNiagaraComponent->Deactivate();
	
	bCanUse=true;
}

void AGun::Fire(FVector CameraLocation,FVector Forward)
{
	FVector End=CameraLocation+Distance*Forward;
	UWorld* World=GetWorld();
	if(World)
	{
		if(GunBullte&&bCanUse)
		{
			/*
			World->SpawnActor<AGunBullte>(Bullte,GetFireLocation(),GetFireRotator());
			*/
			Audio->Activate();
			GunFireNiagaraComponent->Activate();
			Audio->Play();
			Test();
			GunBullte--;
			TArray<AActor*> IgnoreActors;	

			FHitResult HitResult;
			bool bIsHit=UKismetSystemLibrary::LineTraceSingle(GetWorld(), CameraLocation, End, TraceTypeQuery1, true, IgnoreActors, EDrawDebugTrace::None, HitResult, true);
			if(bIsHit)
			{

			}

			if (HitResult.GetActor())
			{
				if(Material)
					UGameplayStatics::SpawnDecalAtLocation(this,Material,FVector(12.5f,12.5f,12.5f),HitResult.Location,FRotator(0.0f,0.0f,0.0f));
				if(AStartLine* Line=Cast<AStartLine>(HitResult.GetActor()))
				{
					
				}
				if(ABaseCar* Car=Cast<ABaseCar>(HitResult.GetActor()))
				{
					Car->Destroy();
				}
				if(ABaseEnemy* Enemy=Cast<ABaseEnemy>(HitResult.GetActor()))
				{
					Enemy->GetHurt(HurtValue+rand()%10);
				}
			}
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
		bCanUse=true;
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
		bCanUse=true;
	}
}

void AGun::SetPhysic(bool Simulate)
{
	GunMesh->SetSimulatePhysics(Simulate);
}

int *AGun::GetCurrnetBullteMessage()
{
	int* array=new int[2];
	array[0]=GunBullte;
	array[1]=LeftGunBullte;
	return array;
}

int AGun::GetMaxBullte()
{
	return MaxBullte;
}


void AGun::GiveUp()
{
	GunMesh->AddForce(FVector(0.0f,10.0f,0.0f));
	SetPhysic(true);
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

