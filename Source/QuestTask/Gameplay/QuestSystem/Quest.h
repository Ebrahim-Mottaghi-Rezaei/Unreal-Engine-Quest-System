// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "QuestItemBase.h"
#include "QuestTask/Components/QuestComponent.h"
#include "QuestTask/DataTypes/Delegates.h"
#include "QuestTask/DataTypes/Enums.h"
#include "QuestTask/DataTypes/Structs.h"
#include "Quest.generated.h"

UCLASS( Abstract, Blueprintable, EditInlineNew )
class QUESTTASK_API UQuest : public UQuestItemBase {
	GENERATED_BODY()

public:
#pragma region event OnStatusChanged

protected:
	UFUNCTION( BlueprintImplementableEvent, Category = "Events", DisplayName="StatusChanged" )
	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void K2_StatusChanged(EQuestStatus NewStatus);

	UFUNCTION( BlueprintCallable )
	FORCEINLINE void Notify_StatusChanged(EQuestStatus NewStatus) {
		OnStatusChanged.Broadcast( NewStatus );
		K2_StatusChanged( NewStatus );
	}

public:
	UPROPERTY( BlueprintCallable, BlueprintAssignable, Category="Event" )
	FQuestStatusChangedDelegate OnStatusChanged;

#pragma endregion

	UQuest();

	virtual ~UQuest() override;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
	EQuestStatus Status;

	UPROPERTY( BlueprintReadWrite, EditAnywhere, meta=(editinlinenew, ShowInnerProperties, FullyExpand=true) )
	TArray<FQuestCondition> CompleteConditions;

	UFUNCTION( BlueprintCallable, Category = "Quest" )
	void UpdateStatus(EQuestStatus NewStatus);

protected:
	UFUNCTION()
	void OnQuestStatusChanged(UQuest* Quest, EQuestStatus NewStatus);

	UQuestComponent* RetrieveQuestComponent() const;

	bool CheckIfConditionsMeet();

	virtual UWorld* GetWorld() const override;

	UPROPERTY()
	TSoftObjectPtr<UQuestComponent> QuestComponent;
};
