#include "BoidSystem.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "BoidsGameModeBase.h"

FVector getDifference(ABoid* b, ABoid* other){
    float dist = FVector::Dist(other->GetActorLocation(), b->GetActorLocation());
    if (FMath::Abs(dist) < DISTANCE) {
        return (other->GetActorLocation() - b->GetActorLocation());
    }
    return FVector(0.0f, 0.0f, 0.0f);
}

void UBoidSystem::initialize(UWorld* world) {

    this->World = world;
    TArray<AActor*> foundActors;
    mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Script/Engine.StaticMesh'/Game/arrow.arrow'")));

    for (int i = 0; i < NUM_BOIDS; i++) {
        makeNewBoid();
    }
}

void UBoidSystem::makeNewBoid(){
    FVector loc = FVector();
    float Y = FMath::RandRange(-START_RANGE, START_RANGE);
    float Z = FMath::RandRange(-START_RANGE, START_RANGE);
    loc.Y = Y;
    loc.Z = Z;
    FRotator rot = FRotator();
    ABoid* newBoid = World->SpawnActor<ABoid>(loc, rot);
    newBoid->setMesh(mesh);
    boids.Add(newBoid);
}

void UBoidSystem::update() {
    for (int i = 0; i < boids.Num(); i++) {
        ABoid* boid = boids[i];
        FVector velocity = addVelocity(boid);
        FVector difference = moveAwayFromBoids(boid);
        
        boid->velocity += BOID_LIMIT*(velocity + difference);
        if (CHECK_GOAL) checkGoal(boid);
    }
}

FVector UBoidSystem::addVelocity(ABoid* b) {
    FVector newLoc = FVector();
    for (int i = 0; i < boids.Num(); i++) {
        ABoid* boid = boids[i];
        if (boid == b) continue;
        newLoc += boid->GetActorLocation();
    }
    newLoc /= (boids.Num() - 1);
    newLoc -= b->GetActorLocation();
    return newLoc * VELOCITY_SCALE;
}

FVector UBoidSystem::moveAwayFromBoids(ABoid* b) {
    FVector c = FVector(0.f);
    for (int i = 0; i < boids.Num(); i++) {
        ABoid* boid = boids[i];
        if (boid == b) continue;
        FVector diff = getDifference(b, boid);
        if (diff.X == 0.0f && diff.Y == 0.0f && diff.Z == 0.0f) continue;
        c -= diff;
    }
    return c;
}


void UBoidSystem::checkGoal(ABoid* b) {
    if ((b->velocity).GetAbs().Size() > GOAL_LIMIT) {
        b->velocity = ((b->velocity) / (b->velocity).GetAbs().Size()) * GOAL_LIMIT;
    }
}


