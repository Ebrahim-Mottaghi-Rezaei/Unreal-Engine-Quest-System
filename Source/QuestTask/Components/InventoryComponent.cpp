// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#include "InventoryComponent.h"
#include "QuestTask/Gameplay/QuestSystem/QuestItemBase.h"

UInventoryComponent::UInventoryComponent() {
	PrimaryComponentTick.bCanEverTick          = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UInventoryComponent::AddToInventory(TSubclassOf<UQuestItemBase> Item, int Count) {
	const auto Id        = Item->GetDefaultObject<UQuestItemBase>()->GetId();
	const auto FoundItem = Inventory.Find( Id );
	if ( FoundItem == nullptr ) {
		Inventory.Add( Id, Count );
		Notify_ItemAdded( Item );
	} else {
		*FoundItem += Count;
		Notify_ItemUpdated( Item, *FoundItem );
	}
}
