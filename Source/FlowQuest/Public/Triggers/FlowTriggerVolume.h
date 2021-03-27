#pragma once

#include "GameFramework/Volume.h"
#include "FlowTriggerVolume.generated.h"

class UFlowTriggerComponent;

UCLASS()
class FLOWQUEST_API AFlowTriggerVolume : public AVolume
{
	GENERATED_UCLASS_BODY()

private:
	UPROPERTY(Category = FlowTriggerBase, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UFlowTriggerComponent* FlowTriggerComponent;
};
