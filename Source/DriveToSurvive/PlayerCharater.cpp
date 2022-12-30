// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharater.h"

#include "GeomUtils/GuContactBuffer.h"

// Sets default values
APlayerCharater::APlayerCharater()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharater::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void APlayerCharater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharater::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void APlayerCharater::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void APlayerCharater::UseGun()
{
	if(PlayerGun)
		GetWorld()->GetTimerManager().SetTimer(Timer,this,&APlayerCharater::GunFire,PlayerGun->GetShotTime(),true);
	else
	{
		
	}
}

void APlayerCharater::StopGun()
{
	GetWorld()->GetTimerManager().ClearTimer(Timer);
}


void APlayerCharater::GunFire()
{
	if(PlayerGun)
		PlayerGun->Fire();
}

void APlayerCharater::DisCardGun()
{
	//解除绑定并扔出枪支
	if(PlayerGun)
		PlayerGun->AddActorLocalOffset(FVector(10.0f,0.0f,0.0f));
	PlayerGun=nullptr;
}


void APlayerCharater::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if(AGun* Gun=Cast<AGun>(Other))
	{
		GunList.Add(Gun);
	}	
}

void APlayerCharater::ActiveMode()
{
	
}


// Called to bind functionality to input
void APlayerCharater::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&APlayerCharater::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&APlayerCharater::MoveRight);
}

