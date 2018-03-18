// Copyright Tianyi

#include "ActorRotator.h"
#include "GameFramework/Actor.h"


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
	auto actor = GetOwner();
	auto new_rotation = FRotator(0.f, 60.f, 0.f);
	actor->SetActorRotation(new_rotation);
	
}


// Called every frame
void UActorRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

