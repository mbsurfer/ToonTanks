// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATower::ATower()
{
    // constructor
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!Tank)
    {
        return;
    }

    // find distance to the Tank
    float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

    // check if the tank is in range
    if (Distance <= FireRange)
    {
         // if in range, rotate turret to the tank
         RotateTurret(Tank->GetActorLocation());
    }

   
}