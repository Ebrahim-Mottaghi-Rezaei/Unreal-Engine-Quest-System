// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "QuestTask/Components/QuestComponent.h"
#include "QuestTask/DataTypes/Delegates.h"
#include "QuestTask/DataTypes/Enums.h"
#include "Quest.generated.h"

class UQuestCondition;

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

	virtual ~UQuest() override;

protected:
	UPROPERTY( BlueprintReadOnly/*, EditAnywhere*/ )
	FGuid Id;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText Name;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText GameplayText;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	UTexture2D* Icon;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
	EQuestStatus Status;

	UPROPERTY( BlueprintReadWrite, EditAnywhere, Instanced, meta=(editinlinenew, ShowInnerProperties, FullyExpand=true) )
	UQuestCondition* Condition;

	UQuestComponent* GetQuestComponent() const;

public:
	FORCEINLINE FGuid GetId() const {
		return Id;
	}

	FORCEINLINE FText GetItemName() const {
		return Name;
	}

	FORCEINLINE FText GetGameplayText() const {
		return GameplayText;
	}

	FORCEINLINE EQuestStatus GetStatus() const {
		return Status;
	}

	UFUNCTION( BlueprintCallable, Category = "Quest" )
	void UpdateStatus(EQuestStatus NewStatus);

protected:
	UFUNCTION()
	void OnQuestStatusChanged(UQuest* Quest, EQuestStatus NewStatus);

	virtual UWorld* GetWorld() const override;

#if WITH_EDITOR
	virtual void PostDuplicate(bool bDuplicateForPIE) override;
#endif

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere )
	TSoftObjectPtr<UQuestComponent> QuestComponent;
};
