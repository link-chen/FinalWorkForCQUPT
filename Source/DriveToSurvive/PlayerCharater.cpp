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
}

// Called when the game starts or when spawned
void APlayerCharater::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate Del;
	Del.BindUFunction(this,"NotifyHit");
	GetCapsuleComponent()->OnComponentHit.Add(Del);

	GetCharacterMovement()->MaxWalkSpeed=300.0f;
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
		if(PlayerGun==nullptr)
		{
			PlayerGun=Gun;
			TakeWeaponRelease();
		}
		if(PlayerGun1==nullptr)
		{
			PlayerGun1=Gun;
			TakeWeaponRelease();
		}
	}
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
	GetCharacterMovement()->MaxWalkSpeed=600.0f;
}

void APlayerCharater::CanncelActiveMode()
{
	GetCharacterMovement()->MaxWalkSpeed=300.0f;
}

void APlayerCharater::TakeWeaponOne()
{
	
}

void APlayerCharater::TakeWeaponTwo()
{
	
}

void APlayerCharater::TakeWeaponRelease()
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
}

