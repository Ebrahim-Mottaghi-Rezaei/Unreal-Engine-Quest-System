// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "QuestCondition.generated.h"

UCLASS( Abstract, Blueprintable, EditInlineNew )
class QUESTTASK_API UQuestCondition : public UObject {
	GENERATED_BODY()

public:
	UQuestCondition();

	virtual ~UQuestCondition() override;

protected:
	UFUNCTION( BlueprintnativeEvent, Category = "QuestCondition" )
	bool Evaluate();

	virtual UWorld* GetWorld() const override;
};
