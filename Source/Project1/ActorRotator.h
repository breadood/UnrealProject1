// Copyright Tianyi

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "ActorRotator.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT1_API UActorRotator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorRotator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();

	void CloseDoor();

	void RotateDoor(float rotation_angle);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
		float OPEN_DOOR_ANGLE = 90.0f;
	UPROPERTY(EditAnywhere)
		float CLOSE_DOOR_ANGLE = 0.0f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* trigger_volume;

	AActor* triggering_actor;
	bool door_is_opened;
};
