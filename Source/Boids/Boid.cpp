#include "Boid.h"
#include "Kismet/KismetMathLibrary.h"

#define BOID_SCALE 2.0f

ABoid::ABoid() {
	PrimaryActorTick.bCanEverTick = true;
	velocity = FVector();
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	RootComponent = mesh;
}

void ABoid::BeginPlay() {
	Super::BeginPlay();
}

void ABoid::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	updateVelocity();
	updateRotation();
}

void ABoid::updateVelocity() {
	SetActorLocation(GetActorLocation() + velocity);
}

void ABoid::updateRotation() {
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(FVector(0.f), velocity);
	SetActorRotation(rotation);
}

void ABoid::setMesh(UStaticMesh* m){
	mesh->SetStaticMesh(m);
	mesh->SetWorldScale3D(FVector(BOID_SCALE, BOID_SCALE, BOID_SCALE));
}