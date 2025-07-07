// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#include "QuestComponent.h"
#include "QuestTask/Gameplay/QuestSystem/Quest.h"

UQuestComponent::UQuestComponent() {
	PrimaryComponentTick.bCanEverTick          = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UQuestComponent::BeginPlay() {
	Super::BeginPlay();
}

void UQuestComponent::AddQuest(TSubclassOf<UQuest> Quest) {
	if ( !ActiveQuests.Contains( Quest.GetDefaultObject()->Info.Id ) ) {
		const auto NewQuest = NewObject<UQuest>( GetOwner(), Quest );

		NewQuest->UpdateStatus( EQuestStatus::Active );
		ActiveQuests.Add( NewQuest->Info.Id, NewQuest );

		Notify_QuestAdded( NewQuest );
	}
}

void UQuestComponent::UpdateQuestStatus(TSubclassOf<UQuest> Quest, EQuestStatus Status) {
	const auto FoundQuest = ActiveQuests.FindRef( Quest.GetDefaultObject()->Info.Id );
	if ( FoundQuest == nullptr )
		return;

	FoundQuest->UpdateStatus( Status );

	if ( Status == EQuestStatus::Completed || Status == EQuestStatus::Failed )
		ActiveQuests.Remove( FoundQuest->Info.Id );
}
