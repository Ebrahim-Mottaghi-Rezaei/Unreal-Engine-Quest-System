﻿// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#include "HasCompletedTasks.h"
#include "Kismet/GameplayStatics.h"
#include "QuestTask/Components/QuestComponent.h"
#include "QuestTask/Gameplay/QuestSystem/Quest.h"
#include "QuestTask/Gameplay/QuestSystem/Interfaces/QuestInterface.h"

UHasCompletedTasks::UHasCompletedTasks() {}

EQuestStatus UHasCompletedTasks::Evaluate_Implementation() {
	const auto PlayerController = UGameplayStatics::GetPlayerController( GetWorld(), 0 );
	if ( !IsValid( PlayerController ) ) {
		UE_LOG( LogTemp, Warning, TEXT("PlayerController is null.") );
		return EQuestStatus::Failed;
	}

	const auto QuestComponent = IQuestInterface::Execute_GetQuestComponent( PlayerController );
	if ( !IsValid( QuestComponent ) ) {
		UE_LOG( LogTemp, Warning, TEXT("InventoryComponent is null.") );
		return EQuestStatus::Failed;
	}

	bool bNotStarted = true;
	bool bCompleted  = true;
	bool bFailed     = false;
	for ( const auto RequiredItem : RequiredQuests ) {
		const auto CurrentStatus = QuestComponent->GetQuestStatus( RequiredItem.GetDefaultObject()->GetId() );

		switch ( CurrentStatus ) {
			case EQuestStatus::NotStarted:
			case EQuestStatus::Active:
				bNotStarted = false;
				bCompleted = false;
				break;
			case EQuestStatus::Failed:
				bFailed = true;
				break;
			default: ;
		}

		if ( bFailed )
			return EQuestStatus::Failed;
	}

	if ( bCompleted )
		return EQuestStatus::Completed;

	if ( bNotStarted ) {
		return EQuestStatus::NotStarted;
	}
	return EQuestStatus::Active;
}
