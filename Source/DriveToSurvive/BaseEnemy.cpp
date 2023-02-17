// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

#include "FPSGameModeBase.h"

void ABaseEnemy::DieOut()
{
	GetWorldTimerManager().ClearTimer(DeleteHandle);
	if(Weapon)
		Weapon->Destroy();
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
	if(BaseWeapon)
	{
		Weapon=GetWorld()->SpawnActor<ABaseWeapon>(BaseWeapon,GetActorLocation(),GetActorRotation());
		Weapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,"hand_rSocket");
		Weapon->SetActorRelativeLocation(Location);
		Weapon->SetActorRelativeRotation(Rotation);
	}
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

float ABaseEnemy::GetCurrentPercent()
{
	return CurrentLife/MaxLife;
}

void ABaseEnemy::HitStart()
{
	if(Weapon)
		Weapon->Start();
}

void ABaseEnemy::HitEnd()
{
	if(Weapon)
		Weapon->End();
}

void ABaseEnemy::PlayDeathAnimation()
{
	if(GetController())
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

