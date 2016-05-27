// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
    // Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	AActor* Owner;
	FRotator OwnerRotator;
	APawn* ActorThatOpens;  // Remember that pawns inherits from actor

	UPROPERTY(VisibleAnywhere)
	int8 MaximumOpenAngle = 90;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

    void OpenDoor(void);
    void CloseDoor(void);

	float GetTotalMassOfActorsOnPlate();
};
