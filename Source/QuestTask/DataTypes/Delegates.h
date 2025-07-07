// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Delegates.generated.h"

UCLASS( Hidden, HideDropdown )
class QUESTTASK_API UDummy : public UObject {
	GENERATED_BODY()
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FQuestAddedDelegate, UQuest*, Quest );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FQuestStatusChangedDelegate, EQuestStatus, NewStatus );