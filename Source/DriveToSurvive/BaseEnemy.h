// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

UCLASS()
class DRIVETOSURVIVE_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float MaxLife;
	float CurrentLife;

	UPROPERTY(EditAnywhere)
	UAnimMontage* DeathMontage;

	UPROPERTY()
	bool bFindEnemy;
	
public:
	// Sets default values for this character's properties
	ABaseEnemy();


	void PlayDeathAnimation();

	bool bLive;

	UFUNCTION(BlueprintCallable)
	void Death();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHurt(float Value);

	UPROPERTY(EditAnywhere)
	FString EnemyLable;
};
