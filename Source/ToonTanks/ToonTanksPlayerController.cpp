// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    if (bPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
        UE_LOG(LogTemp, Warning, TEXT("Start!"));
    }
    else
    {
        GetPawn()->DisableInput(this);
    }

    bShowMouseCursor = bPlayerEnabled;
}