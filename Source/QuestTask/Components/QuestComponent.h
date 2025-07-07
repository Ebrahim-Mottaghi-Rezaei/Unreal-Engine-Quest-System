// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestTask/DataTypes/Delegates.h"
#include "QuestComponent.generated.h"

class UQuest;

UCLASS( ClassGroup=(Game), meta=(BlueprintSpawnableComponent) )
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

	UQuestComponent();

protected:
	UPROPERTY( BlueprintReadOnly )
	TMap<int, UQuest*> ActiveQuests;

	virtual void BeginPlay() override;

public:
	UFUNCTION( BlueprintCallable )
	void AddQuest(TSubclassOf<UQuest> Quest);

	UFUNCTION( BlueprintCallable )
	void UpdateQuestStatus(TSubclassOf<UQuest> Quest, EQuestStatus Status);
};
