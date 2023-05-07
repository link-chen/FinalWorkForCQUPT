// Fill out your copyright notice in the Description page of Project Settings.


#include "CarWheel.h"

#include "PhysXInterfaceWrapperCore.h"
#include "Shape.h"


void UCarWheel::CaculatePerformance()
{
	if(bFirst)//由于UComponent未提供BeginPlay方法，用此分支实现数据初始化
	{
		MaxDestoryNum=Cliff-sqrt((-RateForLine*RateForPow+MaxPerformance-WorstPerformace)/RateForPow);
		bFirst=false;
		this->LatStiffValue=MaxPerformance;
		return;
	}
	if(DestoryNum<Cliff)
	{	//悬崖点前的性能
		CurrentPerformance=-RateForLine*DestoryNum+MaxPerformance;
	}else
	{	//悬崖点后
		CurrentPerformance=RateForPow*pow(CurrentPerformance-MaxDestoryNum,2.0f)+WorstPerformace;
	}
	this->LatStiffValue=CurrentPerformance;
}

UCarWheel::UCarWheel()
{
	MaxDestoryNum=1000.0f;
	DestoryNum=0.0f;

	FScriptDelegate Scr;
	Scr.BindUFunction(this,"OnCompHit");
	CollisionMesh;

	bFirst=true;
}

float UCarWheel::GetLifeRate()
{
	return 1.0f-DestoryNum/MaxDestoryNum;
}

void UCarWheel::Tick(float DeltaSeconds)
{
	if(DestoryNum>=MaxDestoryNum)
	{
		
	}
}
void UCarWheel::Wear(float Value)
{
	float Area=this->ShapeRadius*this->ShapeWidth*2*Pi;//计算参与磨损的面积
	float Delta=Value*WheelRate/Area;//均摊磨损的能量
	DestoryNum+=Delta;
	CaculatePerformance();//计算磨损后的性能
}

float UCarWheel::GetCurrentLife()
{
	return 1.0f-DestoryNum/MaxDestoryNum;
}

void UCarWheel::ReCoverTyre()
{
	DestoryNum=0.0f;
}

float UCarWheel::GetWheelSize()
{
	return this->ShapeRadius;
}

float UCarWheel::GetWheelLength()
{
	return 3.1415926*2*GetWheelSize();
}

float UCarWheel::GetWheelMass()
{
	return Mass;
}


