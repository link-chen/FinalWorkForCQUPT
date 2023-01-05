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

	FScriptDelegate Del;
	Del.BindUFunction(this,"NotifyHit");
	GetCapsuleComponent()->OnComponentHit.Add(Del);

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
	{
		PlayerGun->AddActorLocalOffset(FVector(10.0f,0.0f,0.0f));
		PlayerGun->GiveUp();
	}
	PlayerGun=nullptr;
}


void APlayerCharater::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	// if(AGun* Gun=Cast<AGun>(Other))
	// {
	// 	// GunList.Add(Gun);
	// 	// if(PlayerGun==nullptr)
	// 	// {
	// 	// 	PlayerGun=Gun;
	// 	// 	TakeWeaponRelease();
	// 	// }
	// 	// if(PlayerGun1==nullptr)
	// 	// {
	// 	// 	PlayerGun1=Gun;
	// 	// 	TakeWeaponRelease();
	// 	// }
	// 	if(Gun)
	// 	{
	// 		if(!PlayerGun&&!PlayerGun1)
	// 		{
	// 			PlayerGun=Gun;
	// 			UE_LOG(LogTemp,Warning,TEXT("GunCollision"));
	// 	
	// 			PlayerGun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,"WeaponOne");
	// 			PlayerGun->SetActorRelativeLocation(GunLocation);
	// 			UE_LOG(LogTemp,Warning,TEXT("Add the weapon one"));
	// 			goto even;
	// 		}
	// 		if(PlayerGun&&!PlayerGun1)
	// 		{
	// 			goto even;
	// 		}
	// 		if(!PlayerGun&&PlayerGun1)
	// 		{
	// 			goto even;
	// 		}
	// 		if(PlayerGun&&PlayerGun1)
	// 		{
	// 			goto even;
	// 		}
	// 		even:
	// 			;
	// 	}
	// }
}

void APlayerCharater::OnOverlayBegin(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if(AGun* Gun=Cast<AGun>(Other))
	{
		if(Gun)
		{
			if(!PlayerGun&&!PlayerGun1)
			{
				PlayerGun=Gun;
				UE_LOG(LogTemp,Warning,TEXT("GunCollision"));
		
				PlayerGun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,"WeaponOne");
				PlayerGun->SetActorRelativeLocation(GunAttachLocationOne);
				UE_LOG(LogTemp,Warning,TEXT("Add the weapon one"));
				goto even;
			}
			if(PlayerGun&&!PlayerGun1)
			{
				PlayerGun1=Gun;

				PlayerGun1->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,"WeaponTwo");
				PlayerGun1->SetActorRelativeLocation(GunAttachLocationTwo);
				goto even;
			}
			if(!PlayerGun&&PlayerGun1)
			{
				PlayerGun=Gun;
				goto even;
			}
			if(PlayerGun&&PlayerGun1)
			{
				goto even;
			}
			even:
				;
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

