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
	RotateDoor(OPEN_DOOR_ANGLE);
	door_is_opened = true;
}

void UActorRotator::CloseDoor()
{
	RotateDoor(CLOSE_DOOR_ANGLE);
	door_is_opened = false;
}

void UActorRotator::RotateDoor(float rotation_angle)
{
	GetOwner()->SetActorRotation(FRotator(0.f, rotation_angle, 0.f));;
}




// Called every frame
void UActorRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	bool door_should_open = GetMassOnTrigger(trigger_volume) >= TRIGGER_THRESHOLD;
	// ...
	if (door_should_open && !door_is_opened) {
		OpenDoor();
	}
	else if (!door_should_open && door_is_opened) {
		CloseDoor();
	}
}

float UActorRotator::GetMassOnTrigger(ATriggerVolume* trigger) {
	float total_mass = 0;
	TArray<AActor*> actors_on_trigger;
	trigger->GetOverlappingActors(actors_on_trigger);

	for (const auto actor : actors_on_trigger) {
		total_mass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Trigger has: %s"), *actor->GetName());
	}
	UE_LOG(LogTemp, Warning, TEXT("Total Mass: %f"), total_mass);
	return total_mass;
}
