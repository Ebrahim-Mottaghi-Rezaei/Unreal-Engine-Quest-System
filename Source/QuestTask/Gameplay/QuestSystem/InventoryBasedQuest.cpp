// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#include "InventoryBasedQuest.h"
#include "Conditions/HasItemsCondition.h"
#include "QuestTask/Components/InventoryComponent.h"
#include "QuestTask/DataAssets/GameplayItemData.h"
#include "QuestTask/DataTypes/Structs.h"

UInventoryBasedQuest::UInventoryBasedQuest() {
	InventoryComponent = nullptr;
}

UInventoryBasedQuest::~UInventoryBasedQuest() {
	if ( InventoryComponent.IsValid() ) {
		if ( InventoryComponent->OnItemAdded.IsAlreadyBound( this, &ThisClass::OnItemAddedToInventory ) )
			InventoryComponent->OnItemAdded.AddDynamic( this, &ThisClass::OnItemAddedToInventory );

		if ( InventoryComponent->OnItemUpdated.IsAlreadyBound( this, &ThisClass::OnItemUpdatedInInventory ) )
			InventoryComponent->OnItemUpdated.AddDynamic( this, &ThisClass::OnItemUpdatedInInventory );

		InventoryComponent.Reset();
	}
}

void UInventoryBasedQuest::UpdateStatus(EQuestStatus NewStatus) {
	if ( Status == NewStatus )
		return;

	if ( !IsValid( Condition ) ) {
		UE_LOG( LogTemp, Warning, TEXT( "Condition is null" ) );
		return;
	}

	if ( NewStatus == EQuestStatus::Active ) {
		if ( Condition->Evaluate_Implementation() ) {
			Notify_StatusChanged( EQuestStatus::Completed );
			return;
		}

		if ( !InventoryComponent.IsValid() )
			InventoryComponent = GetInventoryComponent();

		InventoryComponent->OnItemAdded.AddDynamic( this, &ThisClass::OnItemAddedToInventory );
		InventoryComponent->OnItemUpdated.AddDynamic( this, &ThisClass::OnItemUpdatedInInventory );
	}

	Status = NewStatus;
	Notify_StatusChanged( Status );
}

bool UInventoryBasedQuest::CheckForRelevantItem(const UGameplayItemData* Item) const {
	const auto Cond = Cast<UHasItemsCondition>( Condition );
	for ( const auto RequiredItem : Cond->GetRequiredItems() )
		if ( RequiredItem.Item->GetId() == Item->GetId() )
			return true;

	return false;
}

void UInventoryBasedQuest::OnItemAddedToInventory(UGameplayItemData* Item) {
	bool bRelevantItemFound = CheckForRelevantItem( Item );

	if ( bRelevantItemFound && Condition->Evaluate_Implementation() )
		UpdateStatus( EQuestStatus::Completed );
}

void UInventoryBasedQuest::OnItemUpdatedInInventory(UGameplayItemData* Item, uint8 Count) {
	bool bRelevantItemFound = CheckForRelevantItem( Item );

	if ( bRelevantItemFound && Condition->Evaluate_Implementation() )
		UpdateStatus( EQuestStatus::Completed );
}
