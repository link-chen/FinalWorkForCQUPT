// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCar.h"

#include <string>

#include "CarWheel.h"
#include "DriveToSurviveGameModeBase.h"
#include "FPSGameModeBase.h"
#include "WheeledVehicleMovementComponent.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/VarInt.h"

ABaseCar::ABaseCar()
{
	PrimaryActorTick.bCanEverTick = true;
	
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
	LeftPointLight=CreateDefaultSubobject<USpotLightComponent>(TEXT("LeftLight"));
	RightPointLight=CreateDefaultSubobject<USpotLightComponent>(TEXT("RightLight"));
	
	LeftPointLight->SetupAttachment(GetMesh());
	RightPointLight->SetupAttachment(GetMesh());
	bUseLight=true;

	CrashedMaterial=CreateDefaultSubobject<UMaterial>(TEXT("CrashedMaterialRender"));
	
	FScriptDelegate Crash;
	Crash.BindUFunction(this,"OnHit");
	GetMesh()->OnComponentHit.Add(Crash);

	FScriptDelegate HitOn;
	HitOn.BindUFunction(this,"NotifyHit");
	GetMesh()->OnComponentHit.Add(HitOn);
	
}
void ABaseCar::BeginPlay()
{
	Super::BeginPlay();
	ReBornRotator=GetTransform().Rotator();
	LastLocation=GetTransform().GetLocation();
	ElectronicPower=MaxElectronicPower;
	
	UWorld* World=GetWorld();
	if(Widget!=nullptr&&World!=nullptr)
	{
		CarUI=CreateWidget<UUserWidget>(World,Widget);
	}
	UE_LOG(LogTemp,Warning,TEXT("CarUI==%d"),CarUI!=nullptr);
	if(World!=nullptr)
	{
		GameModeBase=Cast<ADriveToSurviveGameModeBase>(World->GetAuthGameMode());
		if(GameModeBase)
		{
			
		}
		if(GameModeBase==nullptr)
		{
			AFPSGameModeBase* GameMode=Cast<AFPSGameModeBase>(World->GetAuthGameMode());
			if(GameMode)
			{
				bCanCarRun=true;
				ReChargeRate=0.5f;
			}
		}
	}

	bStart=false;
	TArray<UVehicleWheel*> TempArray=GetVehicleMovementComponent()->Wheels;

	for(int i=0;i<TempArray.Num();i++)
	{
		CarWheelsArray.Add(Cast<UCarWheel>(TempArray[i]));
	}

	GetWorldTimerManager().SetTimer(Timer,this,&ABaseCar::WearTyre,5,true);

	CarMess=GetVehicleMovementComponent()->Mass;
	
	TurnLight();

	bDraw=false;
	CarUI=false;
}

void ABaseCar::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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
	FVector Down=-GetActorUpVector();
	float Speed=fabs(GetVehicleMovementComponent()->GetForwardSpeed()/100*3.6);
	GetMesh()->AddForce(Down*CarMess*DownForceRate*Speed);
	if(GameModeBase!=nullptr)
	{
		if(GameModeBase->GetCarRunable()&&!bStart)
		{
			bCanCarRun=true;
			bStart=true;
			ShowRunning();
		}
	}
	if(bDraw)
	{
		for(int i=0;i<CarWheelBoneName.Num();i++)
		{
			
			UGameplayStatics::SpawnDecalAtLocation(this,CarWheelMaterial,FVector(30.0f,30.0f,30.0f),GetMesh()->GetSocketLocation(CarWheelBoneName[i]),FRotator(0.0f,0.0f,0.0f));
		}
	}
}

void ABaseCar::ShowRunning()
{
	if(CarUI!=nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("Show"));
		CarUI->AddToViewport();
	}
	else
	{
		CarUI=CreateWidget<UUserWidget>(GetWorld(),Widget);
		CarUI->AddToViewport();
	}
}

void ABaseCar::HideRunning()
{
	if(CarUI!=nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("Hide"));
		CarUI->RemoveFromParent();
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
	GetVehicleMovementComponent()->SetSteeringInput(Value*1.01f);
}

void ABaseCar::Brake()
{
	MoveForward(BrakeBackRate);
	CurrentSpeed=GetVehicleMovementComponent()->GetForwardSpeed()/100.0f;
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
	bDraw=true;
}
void ABaseCar::CancleBrake()
{
	float TempSpeed=GetVehicleMovementComponent()->GetForwardSpeed()/100.0f;
	float DeltaSpeed=CurrentSpeed-TempSpeed;
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
	for(int i=0;i<CarWheelsArray.Num();i++)
	{
		CarWheelsArray[i]->Wear(DeltaSpeed);
	}
	float EPower=GetVehicleMovementComponent()->Mass*DeltaSpeed*DeltaSpeed*ReChargeRate;
	ElectronicPower=ElectronicPower+EPower<=MaxElectronicPower?ElectronicPower+EPower:MaxElectronicPower;
	bDraw=false;
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
	if(Cast<ADriveToSurviveGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		PausedGame();
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

	PlayerInputComponent->BindAction("EndGame",IE_Pressed,this,&ABaseCar::QuitGame);
	
	PlayerInputComponent->BindAction("ChangeCamera",IE_Pressed,this,&ABaseCar::ChangeCamera);
	
	PlayerInputComponent->BindAxis("MoveForward",this,&ABaseCar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ABaseCar::MoveRight);

	PlayerInputComponent->BindAction("Light",IE_Pressed,this,&ABaseCar::TurnLight);
}

void ABaseCar::WearTyre()
{
	for(int i=0;i<CarWheelsArray.Num();i++)
	{
		if(CarWheelsArray[i]!=nullptr)
		{
			CarWheelsArray[i]->Wear(GetVehicleMovementComponent()->GetForwardSpeed()/100.0f*3.6f>3.0f?GetVehicleMovementComponent()->GetForwardSpeed()/100.0f*3.6f/10.0f:0.0f);
			if(CarWheelsArray[i]->GetCurrentLife()<0.0f)
			{
				UE_LOG(LogTemp,Warning,TEXT("CarWheelsArray[%d] Destory"),i);
			}
		}
	}
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
		GetWorldTimerManager().SetTimer(ERSTimeCount,this,&ABaseCar::ERS,ERSTickTime,true);
		bERSCanOpen=true;
	}
	else
	{
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

float ABaseCar::GetGearChangeTime()
{
	return 0.5f;
}
void ABaseCar::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ABaseCar* Car=Cast<ABaseCar>(OtherActor))
	{
		UE_LOG(LogTemp,Warning,TEXT("CarCrashed"));
	}
}

void ABaseCar::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp,Warning,TEXT("Crashed!"));
}

void ABaseCar::TurnLight()
{
	if(bUseLight)
	{
		LeftPointLight->SetIntensity(0.0f);
		RightPointLight->SetIntensity(0.0f);
		bUseLight=false;
	}
	else
	{
		LeftPointLight->SetIntensity(300000.0f);
		RightPointLight->SetIntensity(300000.0f);
		bUseLight=true;
	}
}

void ABaseCar::SetSwitchGearTime(float Time)
{
	UE_LOG(LogTemp,Warning,TEXT("SetGearSwitchTime"));
	UWheeledVehicleMovementComponent4W* WheelMoveComponent=Cast<UWheeledVehicleMovementComponent4W>(GetVehicleMovementComponent());
	if(WheelMoveComponent!=nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("ChangeTime==%f"),WheelMoveComponent->TransmissionSetup.GearSwitchTime);
	}
}

void ABaseCar::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp,Warning,TEXT("OnHit"));
	if(CrashedMaterial)
		UGameplayStatics::SpawnDecalAtLocation(Other,CrashedMaterial,FVector(30.0f,30.0f,30.f),HitLocation,FRotator(0.0f,0.0f,0.0f));
}
