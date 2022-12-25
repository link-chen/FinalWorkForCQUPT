// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireWorkSpawnSpace.h"
#include "RebornPlace.h"
#include "GameFramework/Actor.h"
#include "StartLine.generated.h"

UCLASS()
class DRIVETOSURVIVE_API AStartLine : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Line;
	UPROPERTY(EditAnywhere)
	UBoxComponent* CrossingBox;
	UPROPERTY(EditAnywhere)
	int TargetCircle;
	int Circle;
	
	UPROPERTY(EditAnywhere)
	TArray<ARebornPlace*> RebornArray;
    UPROPERTY(EditAnywhere)
	TArray<AFireWorkSpawnSpace*> FireWorkSpawnSpacesArray;

	void CheckFinish();

	float RacingTime;
	
public:	
	// Sets default values for this actor's properties
	AStartLine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintImplementableEvent)
	void FinishGame();
	void SetCrossTime();
};
