// Copyright Ben Tristem 2016.

#include "BuildingEscape.h"
#include "OpenDoor.h"
#include "Grabber.h"


#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();	
	Owner = GetOwner();
	if (PressurePlate == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName());
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	//UE_LOG(LogTemp, Log, TEXT("Name Actors`s %s "), *GetOwner()->GetName());
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) ///TODO make into a parameter
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	/// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	if (PressurePlate == nullptr) { return TotalMass; }

	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	/// Iterate through them adding their masses
	for (const auto& Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName());
	}
	
	return TotalMass;
}