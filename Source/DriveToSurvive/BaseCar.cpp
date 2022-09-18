// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCar.h"
#include "WheeledVehicleMovementComponent.h"
#include "Components/AudioComponent.h"

ABaseCar::ABaseCar()
{
	ExternalCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("ExternalCamera"));
	InternalCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("InternalCamera"));
	SpringArm=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	ExternalCamera->SetupAttachment(SpringArm);
	InternalCamera->SetupAttachment(RootComponent);
	Audio=CreateDefaultSubobject<UAudioComponent>(TEXT("AudiComponent"));
	InternalCamera->Deactivate();
	bAddForce=true;
	bERSCanOpen=false;
}
void ABaseCar::BeginPlay()
{
	Super::BeginPlay();
	ReBornRotator=GetTransform().Rotator();
	LastLocation=GetTransform().GetLocation();
	ElectronicPower=MaxElectronicPower;
}
void ABaseCar::Tick(float DeltaSeconds)
{
	FVector forward=GetActorForwardVector();
	if(bAddForce)
	{
		if(GetVehicleMovementComponent()->GetForwardSpeed()>0)
		GetMesh()->AddForce(-forward*300000);
	}
	if(bUseERS)
	{
		GetMesh()->AddForce(forward*BaseRate*ERSRate);
	}
}

void ABaseCar::MoveForward(float Value)
{
	GetVehicleMovementComponent()->SetThrottleInput(Value);
	PlayEngineSound();
}

void ABaseCar::MoveRight(float Value)
{
	GetVehicleMovementComponent()->SetSteeringInput(Value);
}

void ABaseCar::Brake()
{
	CurrentSpeed=GetVehicleMovementComponent()->GetForwardSpeed();
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}
void ABaseCar::CancleBrake()
{
	float DeltaSpeed=CurrentSpeed-GetVehicleMovementComponent()->GetForwardSpeed();
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
	ElectronicPower=ElectronicPower+DeltaSpeed/45<=MaxElectronicPower?ElectronicPower+DeltaSpeed/45:MaxElectronicPower;
}

void ABaseCar::PlayEngineSound()
{
	Audio->PitchMultiplier= 0.25f+ (FMath::Abs(GetVehicleMovement()->GetForwardSpeed())*0.045f - 0) / (MaxSpeed - 0)*0.95f;
	if(!Audio->IsPlaying())
	{
		Audio->Play();
	}
}
void ABaseCar::ChangeCamera()
{
	if(bExternal)
	{
		ExternalCamera->Deactivate();
		InternalCamera->Activate();
		bExternal=false;
	}else
	{
		ExternalCamera->Activate();
		InternalCamera->Deactivate();
		bExternal=true;
	}
}

void ABaseCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Brake",IE_Pressed,this,&ABaseCar::Brake);
	PlayerInputComponent->BindAction("Brake",IE_Released,this,&ABaseCar::CancleBrake);
	
	PlayerInputComponent->BindAction("TakeDRS",IE_Pressed,this,&ABaseCar::UseDRS);
	PlayerInputComponent->BindAction("TakeERS",IE_Pressed,this,&ABaseCar::UseERS);

	PlayerInputComponent->BindAction("ReSet",IE_Pressed,this,&ABaseCar::ReSetTransform);
	
	PlayerInputComponent->BindAction("ChangeCamera",IE_Pressed,this,&ABaseCar::ChangeCamera);
	
	PlayerInputComponent->BindAxis("MoveForward",this,&ABaseCar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ABaseCar::MoveRight);
}

void ABaseCar::UseDRS()
{
	if(bInDRSPlace)
	bAddForce=false;
}

void ABaseCar::DisableDRS()
{
	bAddForce=true;
}

void ABaseCar::UseERS()
{
	if(!bERSCanOpen)
	{
		GetWorldTimerManager().SetTimer(ERSTimeCount,this,&ABaseCar::ERS,0.25,true);
		bERSCanOpen=true;
	}
	else
	{
		bERSCanOpen=false;
		GetWorldTimerManager().ClearTimer(ERSTimeCount);
	}
}
void ABaseCar::ERS()
{
	
	if(ElectronicPower!=0.0)
	{
		bUseERS=true;
		ElectronicPower=ElectronicPower-2.5f<0.0f?0.0f:ElectronicPower-2.5f;
	}
	else
	{
		bUseERS=false;
		bERSCanOpen=false;
		GetWorldTimerManager().ClearTimer(ERSTimeCount);
	}
}

void ABaseCar::ReSetTransform()
{
	GetMesh()->SetWorldLocation(LastLocation,false,NULL,ETeleportType::TeleportPhysics);
	GetMesh()->SetWorldRotation(ReBornRotator,false,NULL,ETeleportType::TeleportPhysics);
}

