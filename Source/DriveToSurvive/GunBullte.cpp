// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBullte.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGunBullte::AGunBullte()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	Mesh->SetupAttachment(RootComponent);
	CapsuleComponent=CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AGunBullte::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate Del;
	Del.BindUFunction(this,"NotifyHit");
	CapsuleComponent->OnComponentBeginOverlap.Add(Del);

	AddActorLocalRotation(BullteRotator);
}

void AGunBullte::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if(Material)
	{
		UGameplayStatics::SpawnDecalAtLocation(Other,Material,FVector(30.0f,30.0f,30.f),HitLocation,FRotator(0.0f,0.0f,0.0f));
		UE_LOG(LogTemp,Warning,TEXT("CreateMaterial"));
	}
}

void AGunBullte::OnOverlayBegin(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	
}

// Called every frame
void AGunBullte::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

