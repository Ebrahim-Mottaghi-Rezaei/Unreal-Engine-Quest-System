// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestTask/DataTypes/Delegates.h"
#include "QuestTask/DataTypes/Enums.h"
#include "QuestComponent.generated.h"

class UQuest;

UCLASS( ClassGroup=(QuestTask), meta=(BlueprintSpawnableComponent) )
class QUESTTASK_API UQuestComponent : public UActorComponent {
	GENERATED_BODY()

public:
#pragma region event OnQuestAdded

protected:
	UFUNCTION( BlueprintImplementableEvent, Category = "Events", DisplayName="QuestAdded" )
	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void K2_QuestAdded(UQuest* Quest);

	UFUNCTION( BlueprintCallable )
	FORCEINLINE void Notify_QuestAdded(UQuest* Quest) {
		OnQuestAdded.Broadcast( Quest );
		K2_QuestAdded( Quest );
	}

public:
	UPROPERTY( BlueprintCallable, BlueprintAssignable, Category="Event" )
	FQuestAddedDelegate OnQuestAdded;
#pragma endregion
#pragma region event OnQuestStatusChanged

protected:
	UFUNCTION( BlueprintImplementableEvent, Category = "Events", DisplayName="QuestStatusChanged" )
	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void K2_QuestStatusChanged(UQuest* Quest, EQuestStatus NewStatus);

	UFUNCTION( BlueprintCallable )
	FORCEINLINE void Notify_QuestStatusChanged(UQuest* Quest, EQuestStatus NewStatus) {
		OnQuestStatusChanged.Broadcast( Quest, NewStatus );
		K2_QuestStatusChanged( Quest, NewStatus );
	}

public:
	UPROPERTY( BlueprintCallable, BlueprintAssignable, Category="Event" )
	FQuestStatusUpdatedDelegate OnQuestStatusChanged;
#pragma endregion

	UQuestComponent();

protected:
	UPROPERTY( BlueprintReadOnly )
	TMap<FGuid, UQuest*> ActiveQuests;

public:
	UFUNCTION( BlueprintCallable )
	void AddQuest(TSubclassOf<UQuest> Quest);

	UFUNCTION( BlueprintCallable )
	void UpdateQuestStatus(TSubclassOf<UQuest> Quest, EQuestStatus Status);

	UFUNCTION( BlueprintCallable )
	EQuestStatus GetQuestStatus(const FGuid& QuestId) const;
};
