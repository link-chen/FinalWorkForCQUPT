// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCar.h"


#include "CarWheel.h"
#include "DriveToSurviveGameModeBase.h"
#include "FPSGameModeBase.h"
#include "WheeledVehicleMovementComponent.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void ABaseCar::ShowCarMap()
{
	if(MapWidget)
	{
		MapUI=CreateWidget<UUserWidget>(GetWorld(),MapWidget);
		MapUI->AddToViewport();
	}
}

void ABaseCar::HideCarMap()
{
	if(MapUI!=nullptr)
	{
		MapUI->RemoveFromViewport();
	}else
	{
		
	}
}

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

	bERSCanOpen=false;
	ReChargeRate=0.00005f;
	LeftPointLight=CreateDefaultSubobject<USpotLightComponent>(TEXT("LeftLight"));
	RightPointLight=CreateDefaultSubobject<USpotLightComponent>(TEXT("RightLight"));
	
	LeftPointLight->SetupAttachment(GetMesh());
	RightPointLight->SetupAttachment(GetMesh());
	bUseLight=true;

	CrashedMaterial=CreateDefaultSubobject<UMaterial>(TEXT("CrashedMaterialRender"));

	Weight=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeightComponent"));
	Weight->SetupAttachment(GetMesh());
	
	FScriptDelegate Crash;
	Crash.BindUFunction(this,"OnHit");
	GetMesh()->OnComponentHit.Add(Crash);

	FScriptDelegate HitOn;
	HitOn.BindUFunction(this,"NotifyHit");
	GetMesh()->OnComponentHit.Add(HitOn);

	
}

void ABaseCar::DisBrake()
{
	GetVehicleMovementComponent()->SetBrakeInput(false);
}

float ABaseCar::GetCurrentRPM()
{
	return GetVehicleMovement()!=nullptr?GetVehicleMovement()->GetEngineRotationSpeed():0.0f;
}

float ABaseCar::GetMaxRPM()
{
	return GetVehicleMovement()!=nullptr?GetVehicleMovement()->GetEngineMaxRotationSpeed():0.0f;
}

void ABaseCar::ChangeAirRow()
{
	AirRow-=0.2f;
}

void ABaseCar::ReCoverAirRow()
{
	AirRow+=0.2f;
}

void ABaseCar::BeginPlay()
{
	Super::BeginPlay();
	ReBornRotator=GetTransform().Rotator();
	LastLocation=GetTransform().GetLocation();//设置第一次的重新归位的Location和Rotation
	ElectronicPower=MaxElectronicPower;
	UWorld* World=GetWorld();
	if(Widget!=nullptr&&World!=nullptr)
		CarUI=CreateWidget<UUserWidget>(World,Widget);//添加UI
	if(World!=nullptr)
	{//从游戏模式中获取数据
		GameModeBase=Cast<ADriveToSurviveGameModeBase>(World->GetAuthGameMode());
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
		CarWheelsArray.Add(Cast<UCarWheel>(TempArray[i]));//添加轮胎进行管理
	GetWorldTimerManager().SetTimer(Timer,this,&ABaseCar::WearTyre,5,true);
	CarMess=GetVehicleMovementComponent()->Mass;//初始化质量用于后期进行动能回收计算
	TurnLight();//关灯，在构造函数中灯默认开启
	bDraw=false;
	CarUI=false;
	AirRow=1.29f;
	UWheeledVehicleMovementComponent4W* WheelMoveComponent=Cast<UWheeledVehicleMovementComponent4W>(GetVehicleMovementComponent());
	FVehicleEngineData EngineData=WheelMoveComponent->EngineSetup;
	BaseCurve=EngineData.TorqueCurve;//初始化动力曲线
}

void ABaseCar::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FVector forward=GetActorForwardVector();
	float PowSpeed=pow(fabs(GetVehicleMovementComponent()->GetForwardSpeed()/100),2.0);
	float DragForce=AirRow*PowSpeed*Cd*Square/2.0f;//Air==1.29为空气密度，1.01 equals cd
	if(GetVehicleMovementComponent()->GetForwardSpeed()>0)
		GetMesh()->AddForce(-forward*DragForce);
	DownForce=AirRow*9.8*H;
	FVector Down=-GetActorUpVector();
	GetMesh()->AddForce(Down*PowSpeed*DownForce*DownForceRate);
	if(bUseERS)
	{
		GetMesh()->AddForce(forward*BaseRate*ERSRate);
	}
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
	CarUI=CreateWidget<UUserWidget>(GetWorld(),Widget);
	CarUI->AddToViewport();
}

void ABaseCar::HideRunning()
{
	if(CarUI!=nullptr)
	{
		CarUI->RemoveFromViewport();
	}else
	{
		
	}
}

void ABaseCar::MoveForward(float Value)
{
	if(bCanCarRun)//bCanCarRun由GameMode控制,值为true时车辆可以移动
	{
		if(!bERSCanOpen)//用来区分是否开启混合动力输出
			GetVehicleMovementComponent()->SetThrottleInput(Value*GetInputRate());
		else
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
	CurrentSpeed=GetVehicleMovementComponent()->GetForwardSpeed()/100.0f;//记录刹车前一瞬间的车速
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
	bDraw=true;
}
void ABaseCar::CancleBrake()
{
	float TempSpeed=GetVehicleMovementComponent()->GetForwardSpeed()/100.0f;//获取当前车速
	float DeltaSpeed=CurrentSpeed-TempSpeed;//计算速度增量
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
	float WheelPower;
	for(int i=0;i<CarWheelsArray.Num();i++)
	{
		WheelPower=CarWheelsArray[i]->GetWheelMass()*pow(DeltaSpeed,2.0f)*0.5f;
		CarWheelsArray[i]->Wear(WheelPower);//轮胎磨损
	}
	float EPower=(GetVehicleMovementComponent()->Mass*DeltaSpeed*DeltaSpeed*0.5-4*WheelPower)*ReChargeRate;//除去轮胎的能量后计算可以被回收的能量
	UE_LOG(LogTemp,Warning,TEXT("EPower==%f"),EPower);
	ElectronicPower=ElectronicPower+EPower<=MaxElectronicPower?ElectronicPower+EPower:MaxElectronicPower;//充电
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

	PlayerInputComponent->BindAction("CarMap",IE_Pressed,this,&ABaseCar::ShowCarMap);
	PlayerInputComponent->BindAction("CarMap",IE_Released,this,&ABaseCar::HideCarMap);
}

float ABaseCar::GetInputRate()
{
	if(GetMaxRPM()==0.0f)
		return 0.0f;
	if(GetCurrentRPM()>=StartWorkRate)
		return 1.0f;
	return sqrt(GetCurrentRPM()/GetMaxRPM())>=BaseOutPut?sqrt(GetCurrentRPM()/GetMaxRPM()):BaseOutPut;
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

			}
		}
	}
}

void ABaseCar::UseDRS()
{
	Square-=DeltaSquare;
	H-=DeltaH;
}

void ABaseCar::DisableDRS()
{
	Square+=DeltaSquare;
	H+=DeltaH;
}

void ABaseCar::UseERS()
{
	if(!bERSCanOpen)
	{
		GetWorldTimerManager().SetTimer(ERSTimeCount,this,&ABaseCar::ERS,ERSTickTime,true);
		bERSCanOpen=true;
		UE_LOG(LogTemp,Warning,TEXT("OpenERS"));
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
	//电池电量不为0时
	if(ElectronicPower!=0.0)
	{
		bUseERS=true;
		ElectronicPower=ElectronicPower-ElectronicCost<0.0f?0.0f:ElectronicPower-ElectronicCost;//计算电量消耗
		UWheeledVehicleMovementComponent4W* WheelMoveComponent=Cast<UWheeledVehicleMovementComponent4W>(GetVehicleMovementComponent());
		FVehicleEngineData EngineData=WheelMoveComponent->EngineSetup;
		EngineData.TorqueCurve=ERSCurve;//切换成混合动力发动机的动力输出曲线
		UCarTransData* TransData=Cast<UCarTransData>(WheelMoveComponent);
		if(TransData)//更新引擎参数，不进行更新修改不会起作用
			TransData->UpdateCarEngineSetup(EngineData);
	}
	else
	{
		bUseERS=false;
		bERSCanOpen=false;
		GetWorldTimerManager().ClearTimer(ERSTimeCount);
		UWheeledVehicleMovementComponent4W* WheelMoveComponent=Cast<UWheeledVehicleMovementComponent4W>(GetVehicleMovementComponent());
		FVehicleEngineData EngineData=WheelMoveComponent->EngineSetup;
		EngineData.TorqueCurve=BaseCurve;//切换为纯燃油动力时的动力输出曲线
		UCarTransData* TransData=Cast<UCarTransData>(WheelMoveComponent);
		if(TransData)
			TransData->UpdateCarEngineSetup(EngineData);
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
		
	}
}

void ABaseCar::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	
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
	UWheeledVehicleMovementComponent4W* WheelMoveComponent=Cast<UWheeledVehicleMovementComponent4W>(GetVehicleMovementComponent());
	if(WheelMoveComponent!=nullptr)
	{
		FVehicleTransmissionData Data=WheelMoveComponent->TransmissionSetup;
		Data.GearSwitchTime=Time;
		UCarTransData* TransData=Cast<UCarTransData>(WheelMoveComponent);
		if(TransData)
			TransData->TransmissionReset(Data);
	}
}

void ABaseCar::NotifyHit(UPrimitiveComponent* MyComp,AActor* Other,
	UPrimitiveComponent* OtherComp,bool bSelfMoved,
	FVector HitLocation,FVector HitNormal,
	FVector NormalImpulse,const FHitResult& Hit)
{
	if(CrashedMaterial)
		UGameplayStatics::SpawnDecalAtLocation(Other,CrashedMaterial,
			FVector(30.0f,30.0f,30.f),HitLocation,FRotator(0.0f,0.0f,0.0f));
}

void ABaseCar::ChangeControlForPlayer()
{
	if(PlayerCharacter)
	{
		GetVehicleMovementComponent()->SetHandbrakeInput(true);
		HideRunning();
		PlayerCharacter->GetMesh()->SetVisibility(true,true);
		FVector CarLocation=GetActorLocation();
		PlayerCharacter->SetActorLocation(CarLocation+FVector(100.0f,100.0f,100.0f));
		PlayerCharacter->ShowUI();
		//UnPossessed();
		//PlayerCharacter->PossessedBy(GetController());
		//UGameplayStatics::GetPlayerController(GetWorld(),0);
	}
}
