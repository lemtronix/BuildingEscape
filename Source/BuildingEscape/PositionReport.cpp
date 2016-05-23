// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "PositionReport.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
    FString ObjectPosition = GetOwner()->GetActorLocation().ToString();

    AActor* Owner = GetOwner();

    UE_LOG(LogTemp, Log, TEXT("%s is at Position %s and Rotation %s"), *Owner->GetName(), *Owner->GetActorLocation().ToString(), *Owner->GetActorRotation().ToString());
}


// Called every frame
void UPositionReport::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

