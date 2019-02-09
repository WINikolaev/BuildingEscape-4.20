// Copyright Ben Tristem 2016.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// How far ahead of the player can we reach in cm
	float Reach = 100.f;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPhysicsHandleComponent * PhysicsHandle = nullptr;

	UInputComponent * InputComponent = nullptr;

	/// Setup (assumd) attachd input component
	void SetupInputComponent();
	/// Find attachd physics handle
	void FindPhysicsHandleComponent();
	/// Ray-cast and grab what`s in reach
	void Grab();
	/// Calld when grab ky is releassed
	void Release();
	/// Return hit first physics boy in reach
	const FHitResult GetFirstPhysicsBodyInRach();
	/// Returns current nd of reach line
	FVector GetReachLineStart();
	/// Returns current nd of reach line
	FVector GetReachLineEnd();

	
};
