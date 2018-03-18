// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReporter.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();

	// ...
	auto actor = GetOwner();
	auto name_of_actor = actor->GetName();
	auto position_of_actor = actor->GetActorLocation().ToString();
	// FString position_string = "X: " + position_of_actor.X + ", Y: " + position_of_actor.Y + ", Z: " + position_of_actor.Z;
	UE_LOG(LogTemp, Warning, TEXT("%s is at position %s"), *name_of_actor, *position_of_actor);
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

