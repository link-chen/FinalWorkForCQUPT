// Fill out your copyright notice in the Description page of Project Settings.


#include "MapWidget.h"

bool UMapWidget::Initialize()
{
	if(!Super::Initialize())
		return false;
	RootPanel=Cast<UCanvasPanel>(GetRootWidget());
	if(RootPanel!=nullptr)
	{
		PlayerLocationButton=(UButton*)GetWidgetFromName(TEXT("Button_0"));
		FScriptDelegate Delegate;
		Delegate.BindUFunction(this,"ButtonOnCliek");
		PlayerLocationButton->OnClicked.Add(Delegate);
	}
	return true;
}

void UMapWidget::ButtonOnCliek()
{
}

void UMapWidget::SetPlace(float X, float Y)
{
	
}

void UMapWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
