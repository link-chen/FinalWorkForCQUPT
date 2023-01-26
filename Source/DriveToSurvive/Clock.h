// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DirectionalLight.h"
#include "GameFramework/Actor.h"
#include "Clock.generated.h"

UCLASS()
class DRIVETOSURVIVE_API AClock : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	float TimePerSecond;
	void Count();
	
	FTimerHandle Timer;


public:	
	// Sets default values for this actor's properties
	AClock();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float Speed;
	UPROPERTY(BlueprintReadOnly)
	float RotateNum;

	UFUNCTION(BlueprintCallable)
	float ReturnNum();

	UFUNCTION(BlueprintImplementableEvent)
	void Signal();
};
