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
	BindPhysicsHandler();
	BindInputHandler();
}

void UGrabbingComponent::BindPhysicsHandler()
{
	physics_handle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!physics_handle) {
		UE_LOG(LogTemp, Error, TEXT("Physics handler found"));
	}
}

void UGrabbingComponent::BindInputHandler()
{
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
	if (physics_handle->GrabbedComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Trying to move the component"));

		physics_handle->SetTargetLocation(GetPlayerReach());
	}
}

void UGrabbingComponent::Grab()
{
	FHitResult hit_result;
	GetPhysicsBody(hit_result);
	auto grabbed_component = hit_result.GetComponent();

	if (physics_handle && grabbed_component) {
		physics_handle->GrabComponentAtLocation(grabbed_component, NAME_None, grabbed_component->GetOwner()->GetActorLocation());
		UE_LOG(LogTemp, Warning, TEXT("Grabbing"));
	}
}

void UGrabbingComponent::Release()
{
	if (physics_handle->GrabbedComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Releasing!"));

		physics_handle->ReleaseComponent();
	}
}

void UGrabbingComponent::GetPhysicsBody(FHitResult& hit_result)
{
	FVector player_location = GetPlayerStart();
	FVector player_reach = GetPlayerReach();

	// FHitResult hit_result;
	FCollisionQueryParams collision_param(FName(TEXT("GRAB")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(hit_result, player_location, player_reach, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), collision_param);
}

FVector UGrabbingComponent::GetPlayerReach()
{
	FVector player_location;
	FRotator player_rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(player_location, player_rotation);
	return player_location + player_rotation.Vector() * PLAYER_REACH;
}

FVector UGrabbingComponent::GetPlayerStart()
{
	FVector player_location;
	FRotator player_rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(player_location, player_rotation);
	return player_location;
}

