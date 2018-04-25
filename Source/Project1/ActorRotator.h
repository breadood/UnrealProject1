// Copyright Tianyi

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/TriggerVolume.h"
#include "ActorRotator.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorRequest);


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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetMassOnTrigger(ATriggerVolume * trigger_volume);

	UPROPERTY(BlueprintAssignable)
		FDoorRequest on_open_request;
	UPROPERTY(BlueprintAssignable)
		FDoorRequest on_close_request;

private:
	UPROPERTY(EditAnywhere)
		float TRIGGER_THRESHOLD = 10.0f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* trigger_volume = nullptr;

	AActor* triggering_actor = nullptr;
	bool door_is_opened;
};
