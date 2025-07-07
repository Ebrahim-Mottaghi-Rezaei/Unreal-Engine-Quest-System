// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "QuestTask/DataTypes/Delegates.h"
#include "QuestTask/DataTypes/Enums.h"
#include "QuestTask/DataTypes/Structs.h"
#include "UObject/Object.h"
#include "Quest.generated.h"

class UQuestAsset;

UCLASS( Abstract, Blueprintable, EditInlineNew )
class QUESTTASK_API UQuest : public UObject {
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

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly )
	FQuestInfo Info;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
	EQuestStatus Status;

	UFUNCTION( BlueprintCallable, Category = "Quest" )
	void UpdateStatus(EQuestStatus NewStatus);

	UFUNCTION( BlueprintImplementableEvent, Category = "Quest" )
	void OnQuestActivated(EQuestStatus NewStatus);

	UFUNCTION( BlueprintImplementableEvent, Category = "Quest" )
	void OnQuestCompleted(EQuestStatus NewStatus);

	UFUNCTION( BlueprintImplementableEvent, Category = "Quest" )
	void OnQuestFailed(EQuestStatus NewStatus);

	virtual UWorld* GetWorld() const override;
};
