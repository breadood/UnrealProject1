// Copyright Tianyi

#include "GrabbingComponent.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UGrabbingComponent::UGrabbingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabbingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabbingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FVector player_location;
	FRotator player_rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(player_location, player_rotation);
	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *player_location.ToString(), *player_rotation.ToString());
}

