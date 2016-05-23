// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

    UE_LOG(LogTemp, Log, TEXT("Grabber reporting for duty!"));

    /// Look for attached Physics Handle
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

    if (PhysicsHandle)
    {
        // Found handle
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s: PhysicsHandle Not Found!"), *GetOwner()->GetName());
    }
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    FVector PlayerViewPointVector;
    FRotator PlayerViewPointRotator;

	/// Get the player viewpoint this tick
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointVector, PlayerViewPointRotator);
    
    /// Draw a red trace in the world to visualize
    FVector LineTraceEnd = PlayerViewPointVector + (PlayerViewPointRotator.Vector() * Reach);
    DrawDebugLine(GetWorld(), PlayerViewPointVector, LineTraceEnd, FColor(255, 0, 0), false, 0.0f, 0, 10.0f);

    /// Setup query parameters
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

    /// Line-trace (AKA ray-cast) out to reach distance
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByObjectType(HitResult, PlayerViewPointVector, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);

    // See if we hit anything
    AActor* NewHitActor = HitResult.GetActor();

    if (NewHitActor != nullptr && NewHitActor != LastHitActor)
    {
        UE_LOG(LogTemp, Log, TEXT("Hit %s!"), *NewHitActor->GetName());
        LastHitActor = NewHitActor;
    }
}

