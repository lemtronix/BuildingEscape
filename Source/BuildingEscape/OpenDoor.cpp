// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();	

    Owner = GetOwner();
    OwnerRotator = Owner->GetActorRotation();
    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    // Poll every frame
    // If the actor that opens is in the volume, then open the door
    if (PressurePlate->IsOverlappingActor(ActorThatOpens))
    {
        OpenDoor();
    }
    else
    {
        CloseDoor();
    }
}

void UOpenDoor::OpenDoor()
{
    if (OwnerRotator.Yaw > -MaximumOpenAngle)
    {
        OwnerRotator.Yaw -= 1;
        Owner->SetActorRotation(OwnerRotator);
    }
}

void UOpenDoor::CloseDoor()
{
    if (OwnerRotator.Yaw < 0)
    {
        OwnerRotator.Yaw += 1;
        Owner->SetActorRotation(OwnerRotator);
    }
}
