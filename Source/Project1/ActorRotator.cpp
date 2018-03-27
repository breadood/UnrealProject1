// Copyright Tianyi

#include "ActorRotator.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UActorRotator::UActorRotator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorRotator::BeginPlay()
{
	Super::BeginPlay();

	// ...	
	auto world = GetWorld();
	triggering_actor = world->GetFirstPlayerController()->GetPawn();
	door_is_opened = false;
}

void UActorRotator::OpenDoor()
{
	auto actor = GetOwner();
	auto new_rotation = FRotator(0.f, OPEN_DOOR_ANGLE, 0.f);
	actor->SetActorRotation(new_rotation);
	door_is_opened = true;
}

void UActorRotator::CloseDoor()
{
	auto actor = GetOwner();
	auto new_rotation = FRotator(0.f, CLOSE_DOOR_ANGLE, 0.f);
	actor->SetActorRotation(new_rotation);
	door_is_opened = false;
}


// Called every frame
void UActorRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	bool door_should_open = trigger_volume->IsOverlappingActor(triggering_actor);
	// ...
	if (door_should_open && !door_is_opened) {
		OpenDoor();
	}
	else if (!door_should_open && door_is_opened) {
		CloseDoor();
	}
}

