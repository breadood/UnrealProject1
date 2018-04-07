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
	physics_handle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!physics_handle) {
		UE_LOG(LogTemp, Error, TEXT("No physics handler found"));
		return;
	}

	input_handle = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!input_handle) {
		UE_LOG(LogTemp, Error, TEXT("No input handler found"));
		return;
	}

	input_handle->BindAction("Grab", IE_Pressed, this, &UGrabbingComponent::Grab);
	input_handle->BindAction("Release", IE_Released, this, &UGrabbingComponent::Release);
}


// Called every frame
void UGrabbingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
}

void UGrabbingComponent::Grab()
{
	grabbed_item = TryReachObject();
	if (grabbed_item) {
		UE_LOG(LogTemp, Warning, TEXT("Trying to grab %s!"), *grabbed_item->GetName());
	}
}

void UGrabbingComponent::Release()
{
	if (grabbed_item) {
		UE_LOG(LogTemp, Warning, TEXT("Trying to release!"));
		grabbed_item = nullptr;
	}
}

AActor * UGrabbingComponent::TryReachObject()
{
	FVector player_location;
	FRotator player_rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(player_location, player_rotation);

	FVector player_reach = player_location + player_rotation.Vector() * PLAYER_REACH;

	FHitResult hit_result;
	FCollisionQueryParams collision_param(FName(TEXT("GRAB")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(hit_result, player_location, player_reach, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), collision_param);

	AActor* hit_actor = hit_result.GetActor();
	if (hit_actor) {
		return hit_actor;
	}
	return nullptr;
}

