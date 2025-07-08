// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#include "HasItemsCondition.h"
#include "Kismet/GameplayStatics.h"
#include "QuestTask/Components/InventoryComponent.h"
#include "QuestTask/DataTypes/Structs.h"
#include "QuestTask/Gameplay/QuestSystem/Interfaces/QuestInterface.h"

UHasItemsCondition::UHasItemsCondition() {}

bool UHasItemsCondition::Evaluate_Implementation() {
	const auto PlayerController = UGameplayStatics::GetPlayerController( GetWorld(), 0 );
	if ( !IsValid( PlayerController ) ) {
		UE_LOG( LogTemp, Warning, TEXT("PlayerController is null.") );
		return false;
	}

	const auto InventoryComponent = IQuestInterface::Execute_GetInventoryComponent( PlayerController );
	if ( !IsValid( InventoryComponent ) ) {
		UE_LOG( LogTemp, Warning, TEXT("InventoryComponent is null.") );
		return false;
	}

	for ( const FHasItemsConditionInfo& RequiredItem : RequiredItems )
		if ( InventoryComponent->GetItemCount( RequiredItem.Item ) < RequiredItem.Count )
			return false;

	return true;
}
