// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharater.h"

#include <corecrt_io.h>

#include "BaseCar.h"
#include "FPSGameModeBase.h"
#include "TargetActor.h"
#include "TPSSaveGame.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GeomUtils/GuContactBuffer.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharater::APlayerCharater()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm=CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	SpringArm->SetupAttachment(GetMesh());
	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	CheckCapsule=CreateDefaultSubobject<UCapsuleComponent>(TEXT("CheckCapsuleComponent"));
	CheckCapsule->SetupAttachment(GetMesh());
	WalkSpeed=300.0f;
	RunSpeed=600.0f;

	WaitTime=0.175f;
	
}

// Called when the game starts or when spawned
void APlayerCharater::BeginPlay()
{
	Super::BeginPlay();
	

	GetCharacterMovement()->MaxWalkSpeed=WalkSpeed;
	
	UDel.BindUFunction(this,"OnOverlayBegin");
	GetCapsuleComponent()->OnComponentBeginOverlap.Add(UDel);

	bGun0=false;
	bGun1=false;

	FScriptDelegate Del,OutDel;
	Del.BindUFunction(this,"OnCapsuleBeginOverLap");
	CheckCapsule->OnComponentBeginOverlap.Add(Del);
	OutDel.BindUFunction(this,"OnCapsuleEndOverLap");
	CheckCapsule->OnComponentEndOverlap.Add(OutDel);

	ReadPlayerTargetActor();


	CurrentLife=MaxLife;
	bLive=true;

	ForwardRate=7750.0f;
	bCanAddBreakPoint=false;
}

// Called every frame
void APlayerCharater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CurrentLife<=0.0f&&bLive)
	{
		bLive=false;
		DestroyPlayerInputComponent();
		if(PlayerDieAnimMontage)
			PlayAnimMontage(PlayerDieAnimMontage);
	}
	SetActorRotation(FRotator(GetActorRotation().Pitch,GetActorRotation().Yaw,0.0f));
	LineTracing();
}

void APlayerCharater::MoveForward(float Value)
{
	if(Controller)
	{
		Controller->GetControlRotation().Roll;
		const FRotator YawRotation(0.0f,Controller->GetControlRotation().Yaw,0.0f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction,Value);
	}
}

void APlayerCharater::MoveRight(float Value)
{
	if(Controller)
	{
		const FRotator YawRotation(0.0f,Controller->GetControlRotation().Yaw,0.0f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction,Value);
	}
}

void APlayerCharater::UseGun()
{
	if(PlayerGun)
	{
		GunFire();
		GetWorldTimerManager().SetTimer(Timer,this,&APlayerCharater::GunFire,PlayerGun->GetShotTime(),true);
	}
}

void APlayerCharater::StopGun()
{
	GetWorldTimerManager().ClearTimer(Timer);
}


void APlayerCharater::GunFire()
{
	FVector Start=Camera->GetComponentToWorld().GetLocation();
	FVector Forward=Camera->GetForwardVector();
	if(PlayerGun)
		PlayerGun->Fire(Start,Forward);
}

void APlayerCharater::DisCardGun()
{
	//解除绑定并扔出枪支

	GetCapsuleComponent()->OnComponentBeginOverlap.Remove(UDel);
	
	if(PlayerGun)
	{
		PlayerGun->AddActorLocalOffset(FVector(0.0f,500.0f,0.0f));
		PlayerGun->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		bGun0=false;
		PlayerGun->GiveUp();
	}
	PlayerGun=nullptr;
	ReAddScriptDelegate();
}

TArray<int> APlayerCharater::GetGunBullteMessage()
{
	TArray<int> Message;
	if(PlayerGun)
	{
		int* arr=PlayerGun->GetCurrnetBullteMessage();
		Message.Add(arr[0]);
		Message.Add(arr[1]);
		delete[] arr;
	}
	return  Message;
}

void APlayerCharater::ReLoad()
{
	if(PlayerGun)
	{
		PlayerGun->ReLoadBullte();
	}
}

void APlayerCharater::ReAddScriptDelegate()
{
	GetWorldTimerManager().SetTimer(ReAddDel,this,&APlayerCharater::ReAddScript,WaitTime,false);
}

void APlayerCharater::ReAddScript()
{
	GetCapsuleComponent()->OnComponentBeginOverlap.Add(UDel);
	GetWorldTimerManager().ClearTimer(ReAddDel);
}


void APlayerCharater::PlayerDie()
{
	if(PlayerGun)
	{
		DisCardGun();
	}
	if(PlayerGun1)
	{
		ChangeGun();
		DisCardGun();
	}
	for(int i=0;i<TargetArray.Num();i++)
		TargetArray[i]=0;
	
}

void APlayerCharater::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	
}

void APlayerCharater::OnOverlayBegin(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if(AGun* Gun=Cast<AGun>(Other))
	{
		Gun->SetPhysic(false);
		if(IsGun0Available()&&!IsGun1Available())
		{
			PlayerGun1=Gun;
			if(PlayerGun1==PlayerGun)
			{
				PlayerGun1=nullptr;
				return;
			}
			PlayerGun1->SetActorRelativeLocation(GunAttachLocation);
			PlayerGun1->SetActorRelativeRotation(GunAttachRotator);
			PlayerGun1->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,ReleaseSocket);
			bGun1=true;
		}
		if(!IsGun0Available()&&IsGun1Available())
		{
			PlayerGun=Gun;
			if(PlayerGun1==PlayerGun)
			{
				PlayerGun=nullptr;
				return;
			}
			PlayerGun->SetActorRelativeLocation(FightGunAttachLocation);
			PlayerGun->SetActorRelativeRotation(FightGunAttachRotator);
			PlayerGun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,FightSocket);
			bGun0=true;
		}
		else if(!IsGun0Available()&&!IsGun1Available())
		{
			PlayerGun=Gun;
			PlayerGun->SetActorRelativeLocation(FightGunAttachLocation);
			PlayerGun->SetActorRelativeRotation(FightGunAttachRotator);
			PlayerGun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,FightSocket);
			bGun0=true;
		}
	}
}

void APlayerCharater::OnCapsuleBeginOverLap(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{

	Car=Cast<ABaseCar>(Other)!=nullptr?Cast<ABaseCar>(Other):nullptr;
	PlayerTargetActor=Cast<ATargetActor>(Other)!=nullptr?Cast<ATargetActor>(Other):nullptr;
	Hub=Cast<ASourceCollectHub>(Other)!=nullptr?Cast<ASourceCollectHub>(Other):nullptr;
	Ammunition=Cast<AAmmunition>(Other)!=nullptr?Cast<AAmmunition>(Other):nullptr;
	BreakingPoint=Cast<ABreakingPoint>(Other)!=nullptr?Cast<ABreakingPoint>(Other):nullptr;
}

void APlayerCharater::OnCapsuleEndOverLap(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp)
{
	if(Cast<ABaseCar>(Other))
		Car=nullptr;
	if(Cast<ATargetActor>(Other))
		PlayerTargetActor=nullptr;
	if(Cast<ASourceCollectHub>(Other))
		Hub=nullptr;
	if(Cast<AAmmunition>(Other))
		Ammunition=nullptr;
	if(Cast<ABreakingPoint>(Other))
		BreakingPoint=nullptr;
}


void APlayerCharater::StartJump()
{
	bPressedJump=true;
}

void APlayerCharater::StopJump()
{
	bPressedJump=false;
}

void APlayerCharater::ActiveMode()
{
	GetCharacterMovement()->MaxWalkSpeed=RunSpeed;
	if(PlayerGun)
		PlayerGun->bCanUse=false;
}

void APlayerCharater::CanncelActiveMode()
{
	GetCharacterMovement()->MaxWalkSpeed=WalkSpeed;
	if(PlayerGun)
		PlayerGun->bCanUse=true;
}

void APlayerCharater::TakeWeaponRelease()
{
	if(PlayerGun==nullptr)
	{
		
	}
	if(PlayerGun1==nullptr)
	{
		
	}
	else
	{
		
	}
}

bool APlayerCharater::IsGun1Available()
{
	return bGun1;
}

bool APlayerCharater::IsGun0Available()
{
	return  bGun0;
}

void APlayerCharater::ChangeGun()
{
	AGun* TempGun;
	GetCapsuleComponent()->OnComponentBeginOverlap.Remove(UDel);
	if(IsGun0Available()&&IsGun1Available())
	{
		TempGun=PlayerGun;
		PlayerGun=PlayerGun1;
		PlayerGun1=TempGun;

		PlayerGun->SetActorRelativeLocation(FightGunAttachLocation);
		PlayerGun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,FightSocket);
		PlayerGun1->SetActorRelativeLocation(GunAttachLocation);
		PlayerGun1->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,ReleaseSocket);
	}
	else if(!IsGun0Available()&&IsGun1Available())
	{
		PlayerGun=PlayerGun1;
		PlayerGun1=nullptr;

		PlayerGun->SetActorRelativeLocation(FightGunAttachLocation);
		PlayerGun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,FightSocket);
		
		bGun0=true;
		bGun1=false;
	}
	else if(IsGun0Available()&&!IsGun1Available())
	{
		PlayerGun1=PlayerGun;
		PlayerGun=nullptr;

		PlayerGun1->SetActorRelativeLocation(GunAttachLocation);
		PlayerGun1->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,ReleaseSocket);
		
		bGun0=false;
		bGun1=true;
	}
	ReAddScriptDelegate();
}

void APlayerCharater::PlayReLoadAnimation()
{
	if(IsGun0Available())
	{
		if(PlayerGun->GetCurrnetBullteMessage()[0]!=PlayerGun->GetMaxBullte())
		{
			PlayAnimMontage(ReLoadAnimMontage);
			PlayerGun->bCanUse=false;
		}
	}
}

void APlayerCharater::ShowUI()
{
	UI=CreateWidget(GetWorld(),Fight);
	UI->AddToViewport();
}

void APlayerCharater::HideUI()
{
	if(UI)
	{
		UI->RemoveFromViewport();
	}
}

void APlayerCharater::ChangeControlForCar()
{
	GetMesh()->SetVisibility(false,true);
	Car->PlayerCharacter=this;
	Car->ShowRunning();
	Car->DisBrake();
	HideUI();
	//Car->PossessedBy(GetController());
	//UnPossessed();
	SignalFunc();
}

void APlayerCharater::GetTargetActor()
{
	if(PlayerTargetActor)
	{
		TargetArray[PlayerTargetActor->GetLable()]++;
		PlayerTargetActor->Destroy();
		SavePlayerTargetActor();
	}
}

void APlayerCharater::InteractFunc()
{
	if(Car)
	{
		ChangeControlForCar();
	}
	if(PlayerTargetActor)
	{
		GetTargetActor();
		Cast<AFPSGameModeBase>(GetWorld()->GetAuthGameMode())->BreakPointClear();
		bCanAddBreakPoint=true;
	}
	if(Hub)
	{
		Hub->GetPlayerSource(TargetArray);
		for(int i=0;i<TargetArray.Num();i++)
			TargetArray[i]=0;
	}
	if(Ammunition)
	{
		Ammunition->AddAmmunition(PlayerGun,PlayerGun1);
	}
	if(BreakingPoint)
	{
		if(bCanAddBreakPoint)
			BreakingPoint->SetC4();
		else
		{
			UE_LOG(LogTemp,Error,TEXT("No "))
		}
	}
}

void APlayerCharater::NothingToDo()
{
	
}

void APlayerCharater::SavePlayerTargetActor()
{
	if(UTPSSaveGame* Save=Cast<UTPSSaveGame>(UGameplayStatics::CreateSaveGameObject(UTPSSaveGame::StaticClass())))
	{
		if(Save->PlayerTargetActorNum.Num()==0)
		{
			for(int i=0;i<TargetArray.Num();i++)
			{
				Save->PlayerTargetActorNum.Add(TargetArray[i]);
			}
		}
		else
		{
			for(int i=0;i<TargetArray.Num();i++)
			{
				Save->PlayerTargetActorNum[i]=TargetArray[i];
			}
		}
		if(UGameplayStatics::SaveGameToSlot(Save,"TPSSaveSlot",1))
		{
			
		}
	}
}

void APlayerCharater::ReadPlayerTargetActor()
{
	if(UTPSSaveGame* Read=Cast<UTPSSaveGame>(UGameplayStatics::LoadGameFromSlot("TPSSaveSlot",1)))
	{
		if(Read->PlayerTargetActorNum.Num()==0)
		{
			TargetTypeNum=Cast<AFPSGameModeBase>(GetWorld()->GetAuthGameMode())->TotalTargetNum;
			for(int i=0;i<TargetTypeNum;i++)
				TargetArray.Add(0);
		}
		else
		{
			for(int i=0;i<Read->PlayerTargetActorNum.Num();i++)
				TargetArray.Add(Read->PlayerTargetActorNum[i]);
		}
	}
	else
	{
		TargetTypeNum=Cast<AFPSGameModeBase>(GetWorld()->GetAuthGameMode())->TotalTargetNum;
		for(int i=0;i<TargetTypeNum;i++)
			TargetArray.Add(0);
	}
}

void APlayerCharater::Destroyed()
{
	Super::Destroyed();
	GetCapsuleComponent()->OnComponentBeginOverlap.Remove(UDel);
	if(UI)
	{
		UI->RemoveFromParent();
	}
	if (UWorld* World = GetWorld())
	{
		if (AFPSGameModeBase* GameMode = Cast<AFPSGameModeBase>(World->GetAuthGameMode()))
		{
			GameMode->GetOnPlayerDied().Broadcast(this);
		}
	}
}

void APlayerCharater::ReBorn()
{
	AController* CortollerRef = GetController();
	FVector Location=GetActorLocation();
	Destroy();
	if (UWorld* World = GetWorld())
	{
		if (AFPSGameModeBase* GameMode = Cast<AFPSGameModeBase>(World->GetAuthGameMode()))
		{
			GameMode->RestartPlayer(CortollerRef,Location);
		}
	}
}

void APlayerCharater::ShowMap()
{
	Map=CreateWidget(GetWorld(),MapWidget);
	Map->AddToViewport();
}

void APlayerCharater::DisPlayMap()
{
	if(Map)
	{
		Map->RemoveFromViewport();
	}else
	{
		
	}
}

void APlayerCharater::GetHurt(float Value)
{
	CurrentLife-=Value;
}

void APlayerCharater::LineTracing()
{
	FVector Start=Camera->GetComponentToWorld().GetLocation();
	FVector Forward=Camera->GetForwardVector();
	TArray<AActor*> IgnoreActors;	

	FHitResult HitResult;
	bool bIsHit=UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, Start+Forward*ForwardRate, TraceTypeQuery1, true, IgnoreActors, EDrawDebugTrace::None, HitResult, true);
	if(bIsHit)
	{
		//UKismetSystemLibrary::PrintString(GetWorld(),HitResult.GetActor()->GetName());
		if(ABaseEnemy* Enemy=Cast<ABaseEnemy>(HitResult.GetActor()))
		{
			bCanSeeEnemyBlood=true;
			EnemyPercent=Enemy->GetCurrentPercent();
		}
		else
		{
			bCanSeeEnemyBlood=false;
			EnemyPercent=0.0f;
		}
	}
}

// Called to bind functionality to input
void APlayerCharater::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&APlayerCharater::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&APlayerCharater::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharater::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharater::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&APlayerCharater::StartJump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&APlayerCharater::StartJump);

	PlayerInputComponent->BindAction("TakeERS",IE_Pressed,this,&APlayerCharater::ActiveMode);
	PlayerInputComponent->BindAction("TakeERS",IE_Released,this,&APlayerCharater::CanncelActiveMode);

	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&APlayerCharater::UseGun);
	PlayerInputComponent->BindAction("Fire",IE_Released,this,&APlayerCharater::StopGun);

	PlayerInputComponent->BindAction("ResetVR",IE_Pressed,this,&APlayerCharater::PlayReLoadAnimation);

	PlayerInputComponent->BindAction("ChangeCamera",IE_Pressed,this,&APlayerCharater::ChangeGun);

	PlayerInputComponent->BindAction("GiveUpGun",IE_Pressed,this,&APlayerCharater::DisCardGun);

	PlayerInputComponent->BindAction("TakeChange",IE_Pressed,this,&APlayerCharater::InteractFunc);
	PlayerInputComponent->BindAction("TakeChange",IE_Released,this,&APlayerCharater::NothingToDo);

	PlayerInputComponent->BindAction("TakeDRS",IE_Pressed,this,&APlayerCharater::ShowMap);
	PlayerInputComponent->BindAction("TakeDRS",IE_Released,this,&APlayerCharater::DisPlayMap);

	PlayerInputComponent->BindAction("EndGame",IE_Pressed,this,&APlayerCharater::QuitGame);
}

