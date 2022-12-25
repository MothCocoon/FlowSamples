﻿#include "Core/FlowSaveSubsystem.h"

#include "FlowWorldSettings.h"
#include "Kismet/GameplayStatics.h"

FString UFlowSaveSubsystem::CheckpointSlotName = TEXT("Checkpoint");

UFlowSaveSubsystem::UFlowSaveSubsystem()
	: UFlowSubsystem()
{
}

bool UFlowSaveSubsystem::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	return HasAnyFlags(RF_ClassDefaultObject) ? false : ProcessConsoleExec(Cmd, Ar, nullptr);
}

void UFlowSaveSubsystem::SaveGame()
{
	USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(UFlowSaveGame::StaticClass());
	OnGameSaved(Cast<UFlowSaveGame>(NewSaveGame));

	UGameplayStatics::SaveGameToSlot(NewSaveGame, CheckpointSlotName, 0);
}

void UFlowSaveSubsystem::LoadGame()
{
	USaveGame* LoadedSave = UGameplayStatics::LoadGameFromSlot(CheckpointSlotName, 0);
	if (LoadedSave)
	{
		AbortActiveFlows();
		OnGameLoaded(Cast<UFlowSaveGame>(LoadedSave));

		const UFlowSubsystem* FlowSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UFlowSubsystem>();
		const AFlowWorldSettings* WorldSettings = Cast<AFlowWorldSettings>(GetWorld()->GetWorldSettings());
		if (FlowSubsystem && WorldSettings && WorldSettings->GetFlowComponent()->LoadInstance())
		{
			WorldSettings->GetFlowComponent()->LoadRootFlow();
		}
	}
}
