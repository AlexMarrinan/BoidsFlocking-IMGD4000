
#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Boid.generated.h"

UCLASS()
class ABoid : public AActor
{
public:
	GENERATED_BODY()
	ABoid();
	FVector velocity;
	UStaticMeshComponent* mesh;
	void updateVelocity();
	void updateRotation();
	void setMesh(UStaticMesh* m);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};