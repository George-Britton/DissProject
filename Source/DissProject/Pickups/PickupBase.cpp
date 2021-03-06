// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupBase.h"
#include "../Characters/PlayerCharacter.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Here we initialise the basic components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	PickupMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh Component"));
	PickupMeshComponent->SetupAttachment(this->RootComponent);
	PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Pickup Sphere"));
	PickupSphere->SetupAttachment(this->RootComponent);
}

// Called when a value changes
void APickupBase::OnConstruction(const FTransform& Transform)
{
	// We first set the mesh if it exists
	if (PickupMesh) PickupMeshComponent->SetStaticMesh(PickupMesh);

	// We then update the sphere's radius
	PickupSphere->SetSphereRadius(PickupSphereRadius);
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Here we assign the overlap sphere to register the player overlapping
	PickupSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnSphereOverlapFunction);
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Spin the pickup
	RootComponent->AddLocalRotation(FRotator(0.f, SpinSpeed, 0.f));
}

// This is used to announce when the player overlaps the sphere
void APickupBase::OnSphereOverlapFunction(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OverlappedActor = OtherActor;
	Activate();
}