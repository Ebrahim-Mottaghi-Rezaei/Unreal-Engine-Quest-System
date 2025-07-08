// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuestCondition.h"
#include "HasItemsCondition.generated.h"

struct FHasItemsConditionInfo;
class UGameplayItemData;

UCLASS( BlueprintType )
class QUESTTASK_API UHasItemsCondition : public UQuestCondition {
	GENERATED_BODY()

public:
	UHasItemsCondition();

protected:
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TArray<FHasItemsConditionInfo> RequiredItems;

public:
	FORCEINLINE TArray<FHasItemsConditionInfo> GetRequiredItems() const {
		return RequiredItems;
	}

	virtual bool Evaluate_Implementation() override;
};
