#include "BoidsGameModeBase.h"

#define TICK_RATE 10

ABoidsGameModeBase::ABoidsGameModeBase() {
    PrimaryActorTick.bCanEverTick = true;
}

void ABoidsGameModeBase::BeginPlay() {
    Super::BeginPlay();
    base = NewObject<UBoidSystem>();
    base->initialize(GetWorld());
}

void ABoidsGameModeBase::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    tickNumber++;
    if (tickNumber >= TICK_RATE) {
        base->update();
        tickNumber = 0;
    }
};