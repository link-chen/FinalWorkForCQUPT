// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "SourceCollectHub.h"
#include "TargetActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharater.generated.h"

class ABaseCar;

UCLASS()
class DRIVETOSURVIVE_API APlayerCharater : public ACharacter
{
	GENERATED_BODY()

	//Function For Move
	void MoveForward(float Value);
	void MoveRight(float Value);
	UFUNCTION()
	void StartJump();
	UFUNCTION()
	void StopJump();

	FTimerHandle Timer;

	//Gun
	void UseGun();
	void StopGun();
	void GunFire();
	void DisCardGun();
	AGun* PlayerGun;
	AGun* PlayerGun1;
	bool IsGun1Available();
	bool IsGun0Available();
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;
	
	//Move Speed
	UPROPERTY(EditAnywhere)
	float WalkSpeed;
	UPROPERTY(EditAnywhere)
	float RunSpeed;

	//Animation
	UPROPERTY(EditAnywhere)
	UAnimMontage* ReLoadAnimMontage;
	UPROPERTY(EditAnywhere)
	UAnimMontage* FireAnimMontage;
	UPROPERTY(EditAnywhere)
	UAnimMontage* PlayerDieAnimMontage;

	UFUNCTION(BlueprintCallable)
	TArray<int> GetGunBullteMessage();

	bool bRun;
	
	
	void ActiveMode();
	void CanncelActiveMode();

	void TakeWeaponRelease();

	void ChangeGun();

	UPROPERTY(EditAnywhere)
	FVector GunAttachLocation;
	UPROPERTY(EditAnywhere)
	FRotator GunAttachRotator;
	UPROPERTY(EditAnywhere)
	FVector FightGunAttachLocation;
	UPROPERTY(EditAnywhere)
	FRotator FightGunAttachRotator;
	UPROPERTY(EditAnywhere)
	FName FightSocket;
	UPROPERTY(EditAnywhere)
	FName ReleaseSocket;

	void PlayReLoadAnimation();

	FScriptDelegate UDel;

	void ReAddScriptDelegate();
	void ReAddScript();

	FTimerHandle ReAddDel;

	UPROPERTY(EditAnywhere)
	float WaitTime;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> Fight;
	UUserWidget* UI;

	void PlayerDie();
	
	UFUNCTION()
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	UFUNCTION()
	virtual  void OnOverlayBegin(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	virtual void OnCapsuleBeginOverLap(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	virtual void OnCapsuleEndOverLap(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp);
public:
	// Sets default values for this character's properties
	APlayerCharater();

	UFUNCTION(BlueprintCallable)
	void ReLoad();
	
	UPROPERTY(BlueprintReadOnly)
	bool bGun0;
	UPROPERTY(BlueprintReadOnly)
	bool bGun1;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CheckCapsule;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void ShowUI();
	UFUNCTION(BlueprintCallable)
	void HideUI();

	UPROPERTY(BlueprintReadWrite)
	ABaseCar* Car;
	ATargetActor* PlayerTargetActor;
	ASourceCollectHub* Hub;

	UFUNCTION(BlueprintCallable)
	void ChangeControlForCar();
	void GetTargetActor();

	UPROPERTY(EditAnywhere)
	int TargetTypeNum;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<int> TargetArray;

	void InteractFunc();	
	void NothingToDo();
	
	UFUNCTION(BlueprintImplementableEvent)
	void SignalFunc();

	void SavePlayerTargetActor();
	void ReadPlayerTargetActor();

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	float MaxLife;
	UPROPERTY(BlueprintReadOnly)
	float CurrentLife;
};
