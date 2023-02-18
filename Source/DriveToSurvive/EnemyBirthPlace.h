// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "BaseEnemy.h"
#include "GameFramework/Actor.h"
#include "EnemyBirthPlace.generated.h"

UCLASS()
class DRIVETOSURVIVE_API AEnemyBirthPlace : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABaseEnemy>> EnemyTemplate;
	FTimerHandle Timer;
	void CreateEnemy();
	UPROPERTY(EditAnywhere)
	float CreateTime;
	bool bCanUse;
public:	
	// Sets default values for this actor's properties
	AEnemyBirthPlace();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetUseable(bool CanUse);
};
