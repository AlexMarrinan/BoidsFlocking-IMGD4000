#pragma once

#include "CoreMinimal.h"
#include "Boid.h"
#include "Engine/GameEngine.h"
#include "BoidSystem.generated.h"

#define NUM_BOIDS 50
#define DISTANCE 100
#define BOID_LIMIT 0.5f
#define START_RANGE 1200
#define VELOCITY_SCALE 1/85

#define CHECK_GOAL false
#define GOAL_LIMIT 30

UCLASS()
class UBoidSystem : public UObject
{

public:
	GENERATED_BODY()
	void initialize(UWorld* world);
	void makeNewBoid();
	void update();
	void checkGoal(ABoid* b);
	FVector addVelocity(ABoid* b);
	FVector moveAwayFromBoids(ABoid* b);
private:
	UWorld* World;
	UStaticMesh* mesh;	
	TArray<class ABoid*> boids;
};