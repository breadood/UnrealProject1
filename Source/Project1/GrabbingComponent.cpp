// Copyright Tianyi

#include "GrabbingComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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

	FVector player_reach = player_location + player_rotation.Vector() * PLAYER_REACH;
	DrawDebugLine(GetWorld(), player_location, player_reach, FColor(0, 0, 255), false, 0.0f, 0, 10.0f);
	//UE_LOG(LogTemp, Warning, TEXT("Player is reaching position %s"), *player_reach.ToString());
}

