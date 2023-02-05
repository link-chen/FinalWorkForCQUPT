// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

void ABaseEnemy::DieOut()
{
	GetWorldTimerManager().ClearTimer(DeleteHandle);
	Destroy();
}

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	CurrentLife=MaxLife;
	bLive=true;
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CurrentLife<=0.0f&&bLive)
	{
		bLive=false;
		PlayDeathAnimation();
	}
}
void ABaseEnemy::GetHurt(float Value)
{
	CurrentLife-=Value;
	if(HurtMontage)
		PlayAnimMontage(HurtMontage);
}

void ABaseEnemy::PlayDeathAnimation()
{
	GetController()->Destroy();
	if(DeathMontage)
		PlayAnimMontage(DeathMontage);
}

void ABaseEnemy::Death()
{
	GetWorldTimerManager().SetTimer(DeleteHandle,this,&ABaseEnemy::DieOut,DeleteTime,false);
}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

