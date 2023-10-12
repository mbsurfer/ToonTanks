// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    // first check to see if the detroyed actor was the tank player
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();

        if (ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
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
    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (Tank)
    {
        ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

        StartGame();

        if (ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);

            // Enable the player at the end of the timer
            FTimerHandle PlayerEnableTimerHandle;
            FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
                ToonTanksPlayerController,
                &AToonTanksPlayerController::SetPlayerEnabledState,
                true
            );

            UE_LOG(LogTemp, Warning, TEXT("Game will start in %f seconds."), StartDelay);

            // Create a timer to start the game
            GetWorldTimerManager().SetTimer(
                PlayerEnableTimerHandle,
                PlayerEnableTimerDelegate,
                StartDelay,
                false
            );
        }
    }
}