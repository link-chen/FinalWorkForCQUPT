// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharater.h"

#include <corecrt_io.h>

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GeomUtils/GuContactBuffer.h"

// Sets default values
APlayerCharater::APlayerCharater()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm=CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	SpringArm->SetupAttachment(GetMesh());
	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	WalkSpeed=300.0f;
	RunSpeed=600.0f;
}

// Called when the game starts or when spawned
void APlayerCharater::BeginPlay()
{
	Super::BeginPlay();
	

	GetCharacterMovement()->MaxWalkSpeed=WalkSpeed;

	FScriptDelegate UDel;
	UDel.BindUFunction(this,"OnOverlayBegin");
	GetCapsuleComponent()->OnComponentBeginOverlap.Add(UDel);
}

// Called every frame
void APlayerCharater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharater::MoveForward(float Value)
{
	Controller->GetControlRotation().Roll;
	const FRotator YawRotation(0.0f,Controller->GetControlRotation().Yaw,0.0f);
	const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
	AddMovementInput(Direction,Value);
	/*
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
	*/
}

void APlayerCharater::MoveRight(float Value)
{
	const FRotator YawRotation(0.0f,Controller->GetControlRotation().Yaw,0.0f);
	const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
	AddMovementInput(Direction,Value);
	/*
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
	*/
}

void APlayerCharater::UseGun()
{
	if(PlayerGun)
	{
		UE_LOG(LogTemp,Warning,TEXT("StartFire,shot time==%f"),PlayerGun->GetShotTime());
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
	UE_LOG(LogTemp,Warning,TEXT("Using Gun"));
	if(PlayerGun)
		PlayerGun->Fire();
}

void APlayerCharater::DisCardGun()
{
	//解除绑定并扔出枪支
	if(PlayerGun)
	{
		PlayerGun->AddActorLocalOffset(FVector(10.0f,0.0f,0.0f));
		PlayerGun->GiveUp();
	}
	PlayerGun=nullptr;
}


void APlayerCharater::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	
}

void APlayerCharater::OnOverlayBegin(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if(AGun* Gun=Cast<AGun>(Other))
	{
		if(!IsGun0Available()&&!IsGun1Available())
		{
			UE_LOG(LogTemp,Warning,TEXT("1"));
			PlayerGun=Gun;
			PlayerGun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,"Weapon");
			PlayerGun->SetActorRelativeLocation(FightGunAttachLocation);
			bGun0=true;
		}
		else if(IsGun0Available()&&!IsGun1Available())
		{
			UE_LOG(LogTemp,Warning,TEXT("2"));
			PlayerGun1=Gun;
			PlayerGun1->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,"ReleaseWeapon");
			PlayerGun1->SetActorRelativeLocation(GunAttachLocation);
			bGun1=true;
		}
		else if(!IsGun0Available()&&IsGun1Available())
		{
			UE_LOG(LogTemp,Warning,TEXT("3"));
			PlayerGun=Gun;
			PlayerGun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,"Weapon");
			PlayerGun->SetActorRelativeLocation(GunAttachLocation);
			bGun0=true;
		}
	}
}


void APlayerCharater::StartJump()
{
	bPressedJump=true;
	bPressedJump=true;
}

void APlayerCharater::StopJump()
{
	bPressedJump=false;
}



void APlayerCharater::ActiveMode()
{
	GetCharacterMovement()->MaxWalkSpeed=RunSpeed;
}

void APlayerCharater::CanncelActiveMode()
{
	GetCharacterMovement()->MaxWalkSpeed=WalkSpeed;
}

void APlayerCharater::TakeWeaponOne()
{
	
}

void APlayerCharater::TakeWeaponTwo()
{
	
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
		UE_LOG(LogTemp,Warning,TEXT("Can not get any weapon"));
	}
}

bool APlayerCharater::IsGun1Available()
{
	return bGun0;
}

bool APlayerCharater::IsGun0Available()
{
	return  bGun1;
}

void APlayerCharater::ChangeGun()
{
	
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

	PlayerInputComponent->BindAction("WeaponOne",IE_Pressed,this,&APlayerCharater::TakeWeaponOne);
	PlayerInputComponent->BindAction("WeaponTwo",IE_Pressed,this,&APlayerCharater::TakeWeaponTwo);

	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&APlayerCharater::UseGun);
	PlayerInputComponent->BindAction("Fire",IE_Released,this,&APlayerCharater::StopGun);
}

