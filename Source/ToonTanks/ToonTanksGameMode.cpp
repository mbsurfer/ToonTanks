// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    // first check to see if the detroyed actor was the tank player
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();

        if (APlayerController* PlayerController = Tank->GetTankPlayerController())
        {
            Tank->DisableInput(PlayerController);
            PlayerController->bShowMouseCursor = false;
            UE_LOG(LogTemp, Warning, TEXT("You are dead."));
        }
    }
    // check if the destroyed actor was a tower
    else if (ATower* DetroyedTower = Cast<ATower>(DeadActor))
    {
        DetroyedTower->HandleDestruction();
        UE_LOG(LogTemp, Warning, TEXT("You destroyed a tower!"));
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}