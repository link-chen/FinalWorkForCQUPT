// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

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
}

void ABaseEnemy::PlayDeathAnimation()
{
	PlayAnimMontage(DeathMontage);
}

void ABaseEnemy::Death()
{
	GetController()->Destroy();
}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

