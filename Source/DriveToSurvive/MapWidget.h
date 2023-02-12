// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/UserWidget.h"
#include "MapWidget.generated.h"

/**
 * 
 */
UCLASS()
class DRIVETOSURVIVE_API UMapWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UButton* PlayerLocationButton;
	UCanvasPanel* RootPanel;


	virtual bool Initialize() override;
	
	UFUNCTION(BlueprintCallable)
	void ButtonOnCliek();
	
	UFUNCTION(BlueprintCallable)
	void SetPlace(float X,float Y);
protected:
	virtual void NativeConstruct() override;
};
