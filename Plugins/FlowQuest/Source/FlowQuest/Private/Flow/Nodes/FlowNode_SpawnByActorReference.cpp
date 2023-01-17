// Copyright https://github.com/MothCocoon/FlowSolo/graphs/contributors

#include "Flow/Nodes/FlowNode_SpawnByActorReference.h"

UFlowNode_SpawnByActorReference::UFlowNode_SpawnByActorReference(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("World");
#endif

	InputPins = {TEXT("Spawn"), TEXT("Despawn")};
	OutputPins = {TEXT("Spawned"), TEXT("Despawned")};
}

void UFlowNode_SpawnByActorReference::ExecuteInput(const FName& PinName)
{
	if (SpawnPoints.Num() > 0)
	{
		if (PinName == TEXT("Spawn"))
		{
			int32 SpawnCount = 0;

			for (const TSoftObjectPtr<AActor>& SpawnPoint : SpawnPoints)
			{
				if (const AActor* SpawnActor = SpawnPoint.LoadSynchronous())
				{
					TArray<USpawnComponent*> FoundComponents;
					SpawnActor->GetComponents<USpawnComponent>(FoundComponents);
					for (USpawnComponent* FoundComponent : FoundComponents)
					{
						if (!SpawnComponents.Contains(FoundComponent))
						{
							if (FoundComponent->Spawn(SpawnParams))
							{
								SpawnComponents.Emplace(FoundComponent);
								SpawnCount++;
							}
						}
					}
				}
			}

			if (SpawnCount > 0)
			{
				TriggerOutput(TEXT("Spawned"));
			}
		}
		else if (PinName == TEXT("Despawn"))
		{
			int32 DespawnCount = 0;
			for (TWeakObjectPtr<USpawnComponent> SpawnComponent : SpawnComponents)
			{
				if (SpawnComponent.IsValid())
				{
					SpawnComponent->Despawn();
					DespawnCount++;
				}
			}

			if (DespawnCount > 0)
			{
				TriggerOutput(TEXT("Despawned"), true);
			}
		}
	}
	else
	{
		LogError(MissingIdentityTag);
	}
}

void UFlowNode_SpawnByActorReference::Cleanup()
{
	SpawnComponents.Empty();
}

#if WITH_EDITOR
FString UFlowNode_SpawnByActorReference::GetNodeDescription() const
{
	const FString ClassString = SpawnParams.ActorClass ? SpawnParams.ActorClass->GetFName().ToString() : TEXT("Missing Actor Class!");
	return (SpawnPoints.Num() > 0 ? FString::Printf(TEXT("%d spawn points"), SpawnPoints.Num()) : TEXT("No spawn points!")) + LINE_TERMINATOR + ClassString;
}

EDataValidationResult UFlowNode_SpawnByActorReference::ValidateNode()
{
	if (SpawnPoints.Num() == 0 || SpawnParams.ActorClass == nullptr)
	{
		if (SpawnPoints.Num() == 0)
		{
			ValidationLog.Error<UFlowNode>(TEXT("No Spawn Points assigned"), this);
		}
		if (SpawnParams.ActorClass == nullptr)
		{
			ValidationLog.Error<UFlowNode>(TEXT("Actor Class is missing or invalid"), this);
		}

		return EDataValidationResult::Invalid;
	}

	return EDataValidationResult::Valid;
}
#endif
