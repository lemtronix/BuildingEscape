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

    // If the actor that opens is in the volume, then open the door
    if (GetTotalMassOfActorsOnPlate() > 30.0f)
    {
		// PressurePlate->IsOverlappingActor(ActorThatOpens)
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

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActorsOnPressurePlate;

	// Find all the overlapping actors
	PressurePlate->GetOverlappingActors(OverlappingActorsOnPressurePlate);

	// Iterate through them adding their masses
	for (const auto& EachActor : OverlappingActorsOnPressurePlate)
	{
		TotalMass += EachActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

		UE_LOG(LogTemp, Log, TEXT("%s on pressure plate %f"), *EachActor->GetName(), TotalMass);
	}

	return TotalMass;
}