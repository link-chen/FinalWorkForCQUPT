// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCar.h"

#include "DriveToSurviveGameModeBase.h"
#include "WheeledVehicleMovementComponent.h"
#include "WheeledVehicleMovementComponent4W.h"
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
	ReChargeRate=0.00005f;
	UWheeledVehicleMovementComponent4W *MovementComponent4W=Cast<UWheeledVehicleMovementComponent4W>(GetVehicleMovementComponent());
	MovementComponent4W->TransmissionSetup.GearSwitchTime=0.1f;	
}
void ABaseCar::BeginPlay()
{
	Super::BeginPlay();
	ReBornRotator=GetTransform().Rotator();
	LastLocation=GetTransform().GetLocation();
	ElectronicPower=MaxElectronicPower;
	UWorld* World=GetWorld();
	if(World!=nullptr)
	{
		GameModeBase=Cast<ADriveToSurviveGameModeBase>(World->GetAuthGameMode());
	}
	bStart=false;
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
	FVector Down=FVector(0,0,-1);
	float Speed=fabs(GetVehicleMovementComponent()->GetForwardSpeed()/100*3.6);
	GetMesh()->AddForce(Down*BaseRate*DownForceRate*Speed);
	if(GameModeBase!=nullptr)
	{
		if(GameModeBase->GetCarRunable()&&!bStart)
		{
			bCanCarRun=true;
			bStart=true;
			LightOut();
			UE_LOG(LogTemp,Warning,TEXT("Let's Go!"))
		}
	}
}

void ABaseCar::MoveForward(float Value)
{
	if(bCanCarRun)
	{
		GetVehicleMovementComponent()->SetThrottleInput(Value);
		PlayEngineSound();
	}
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
	float DeltaSpeed=CurrentSpeed-GetVehicleMovementComponent()->GetForwardSpeed()/100.0f;
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
	float EPower=GetVehicleMovementComponent()->Mass*DeltaSpeed*DeltaSpeed*0.5f*ReChargeRate;
	ElectronicPower=ElectronicPower+EPower<=MaxElectronicPower?ElectronicPower+EPower:MaxElectronicPower;
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
void ABaseCar::QuitGame()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("QUIT");
}

void ABaseCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Brake",IE_Pressed,this,&ABaseCar::Brake);
	PlayerInputComponent->BindAction("Brake",IE_Released,this,&ABaseCar::CancleBrake);
	
	PlayerInputComponent->BindAction("TakeDRS",IE_Pressed,this,&ABaseCar::UseDRS);
	PlayerInputComponent->BindAction("TakeERS",IE_Pressed,this,&ABaseCar::UseERS);

	PlayerInputComponent->BindAction("ReSet",IE_Pressed,this,&ABaseCar::ReSetTransform);

	PlayerInputComponent->BindAction("EndGame",IE_Pressed,this,&ABaseCar::QuitGame);
	
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
		UE_LOG(LogTemp,Warning,TEXT("ERSOn"));
		GetWorldTimerManager().SetTimer(ERSTimeCount,this,&ABaseCar::ERS,ERSTickTime,true);
		bERSCanOpen=true;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("ERSOff"));
		bERSCanOpen=false;
		bUseERS=false;
		GetWorldTimerManager().ClearTimer(ERSTimeCount);
	}
}
void ABaseCar::ERS()
{
	
	if(ElectronicPower!=0.0)
	{
		bUseERS=true;
		ElectronicPower=ElectronicPower-ElectronicCost<0.0f?0.0f:ElectronicPower-ElectronicCost;
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

float ABaseCar::GetERSRate()
{
	return ERSRate;
}
void ABaseCar::SetERSRate(float Value)
{
	ERSRate=Value<=12.0f?Value:12.0f;
}

float ABaseCar::GetDownForceRate()
{
	return DownForceRate;
}

void ABaseCar::SetDownForceRate(float Value)
{
	DownForceRate=Value;
}

float ABaseCar::GetReChargeRate()
{
	return ReChargeRate;
}

void ABaseCar::SetReChargeRate(float Value)
{
	ReChargeRate=Value;
}

float ABaseCar::GetGeerChangeTime()
{
	return 0.5f;
}

void ABaseCar::SetGeerChangeTime(float Value)
{
	UWheeledVehicleMovementComponent4W *MovementComponent4W=Cast<UWheeledVehicleMovementComponent4W>(GetVehicleMovementComponent());
	MovementComponent4W->TransmissionSetup.GearSwitchTime=0.1f;	
}

