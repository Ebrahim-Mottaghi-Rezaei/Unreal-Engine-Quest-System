// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestTask/DataTypes/Delegates.h"
#include "InventoryComponent.generated.h"

class UQuestItemBase;

UCLASS( ClassGroup=(QuestTask), meta=(BlueprintSpawnableComponent) )
class QUESTTASK_API UInventoryComponent : public UActorComponent {
	GENERATED_BODY()

public:
#pragma region event OnItemAdded

protected:
	UFUNCTION( BlueprintImplementableEvent, Category = "Events", DisplayName="ItemAdded" )
	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void K2_ItemAdded(TSubclassOf<UQuestItemBase> Item);

	UFUNCTION( BlueprintCallable )
	FORCEINLINE void Notify_ItemAdded(TSubclassOf<UQuestItemBase> Item) {
		OnItemAdded.Broadcast( Item );
		K2_ItemAdded( Item );
	}

public:
	UPROPERTY( BlueprintCallable, BlueprintAssignable, Category="Event" )
	FInventoryItemAddedDelegate OnItemAdded;
#pragma endregion

#pragma region event OnItemUpdated

protected:
	UFUNCTION( BlueprintImplementableEvent, Category = "Events", DisplayName="ItemUpdated" )
	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void K2_ItemUpdated(TSubclassOf<UQuestItemBase> Item, uint8 Count);

	UFUNCTION( BlueprintCallable )
	FORCEINLINE void Notify_ItemUpdated(TSubclassOf<UQuestItemBase> Item, uint8 Count) {
		OnItemUpdated.Broadcast( Item, Count );
		K2_ItemUpdated( Item, Count );
	}

public:
	UPROPERTY( BlueprintCallable, BlueprintAssignable, Category="Event" )
	FInventoryItemUpdatedDelegate OnItemUpdated;
#pragma endregion
	UInventoryComponent();

protected:
	UPROPERTY( BlueprintReadOnly )
	TMap<FGuid, uint8> Inventory;

	UFUNCTION( BlueprintCallable )
	void AddToInventory(TSubclassOf<UQuestItemBase> Item, int Count);
};
