// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestInterface.generated.h"

class UQuestComponent;

UINTERFACE()
class UQuestInterface : public UInterface {
	GENERATED_BODY()
};

class QUESTTASK_API IQuestInterface {
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category="Quest Interface" )
	UQuestComponent* GetQuestComponent();
};
