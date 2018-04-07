// Copyright Tianyi

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabbingComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT1_API UGrabbingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabbingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
private:
	UPROPERTY(EditAnywhere)
		float PLAYER_REACH = 100.0f;
	
	UPhysicsHandleComponent* physics_handle = nullptr;
	UInputComponent* input_handle = nullptr;
	AActor* grabbed_item = nullptr;

	void Grab();

	void Release();

	AActor* TryReachObject();

	
};
