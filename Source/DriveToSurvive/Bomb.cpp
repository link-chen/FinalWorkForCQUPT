// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"

#include "PlayerCharater.h"

void ABomb::Finish()
{
	Destroy();
}

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoomSphereComponent=CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	NiagaraComponent=CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	NiagaraComponent->SetupAttachment(BoomSphereComponent);
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate Del;
	Del.BindUFunction(this,"OnOverlayBegin");
	BoomSphereComponent->OnComponentBeginOverlap.Add(Del);

	GetWorldTimerManager().SetTimer(Timer,this,&ABomb::Finish,ExitTime,false);
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BoomSphereComponent->SetSphereRadius(BoomSphereComponent->GetUnscaledSphereRadius()+UpRate);
}

void ABomb::SetBoomValue(float Value)
{
	HurtValue=Value;
}

void ABomb::OnOverlayBegin(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if(APlayerCharater* Player=Cast<APlayerCharater>(Other))
	{
		if(Character==nullptr)
		{
			Character=Player;
			Player->CurrentLife-=HurtValue;
		}
	}
}

