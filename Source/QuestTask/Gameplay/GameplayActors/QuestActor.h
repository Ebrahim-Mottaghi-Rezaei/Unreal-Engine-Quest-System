// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestActor.generated.h"

class UQuest;

UCLASS( Blueprintable )
class QUESTTASK_API AQuestActor : public AActor {
	GENERATED_BODY()

public:
	AQuestActor();

protected:
	UPROPERTY( BlueprintReadOnly, EditAnywhere )
	TSubclassOf<UQuest> Quest;
};
