// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#include "HasCompletedTasks.h"
#include "Kismet/GameplayStatics.h"
#include "QuestTask/Components/QuestComponent.h"
#include "QuestTask/Gameplay/QuestSystem/Quest.h"
#include "QuestTask/Gameplay/QuestSystem/Interfaces/QuestInterface.h"

UHasCompletedTasks::UHasCompletedTasks() {}

bool UHasCompletedTasks::Evaluate_Implementation() {
	const auto PlayerController = UGameplayStatics::GetPlayerController( GetWorld(), 0 );
	if ( !IsValid( PlayerController ) ) {
		UE_LOG( LogTemp, Warning, TEXT("PlayerController is null.") );
		return false;
	}

	const auto QuestComponent = IQuestInterface::Execute_GetQuestComponent( PlayerController );
	if ( !IsValid( QuestComponent ) ) {
		UE_LOG( LogTemp, Warning, TEXT("InventoryComponent is null.") );
		return false;
	}

	for ( const auto RequiredItem : RequiredQuests )
		if ( QuestComponent->GetQuestStatus( RequiredItem.GetDefaultObject()->GetId() ) != EQuestStatus::Completed )
			return false;

	return true;
}
