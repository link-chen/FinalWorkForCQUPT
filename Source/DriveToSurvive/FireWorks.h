// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "FireWorks.generated.h"

UCLASS()
class DRIVETOSURVIVE_API AFireWorks : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* TailComponent;
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* BoomComponent;
	bool bBoomed;
	
	UPROPERTY(EditAnywhere)
	float MaxHeight;
	
public:	
	// Sets default values for this actor's properties
	AFireWorks();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	UFUNCTION(BlueprintImplementableEvent)
	void Boom();
	UPROPERTY(BlueprintReadOnly)
	float Time;
	virtual void Tick(float DeltaTime) override;

};
