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
	const auto Id = Quest.GetDefaultObject()->GetId();
	if ( !ActiveQuests.Contains( Id ) ) {
		const auto NewQuest = NewObject<UQuest>( GetOwner(), Quest );
		ActiveQuests.Add( Id, NewQuest );

		Notify_QuestAdded( NewQuest );

		NewQuest->UpdateStatus( EQuestStatus::Active );
		Notify_QuestStatusChanged( NewQuest, EQuestStatus::Active );
	}
}

void UQuestComponent::UpdateQuestStatus(const TSubclassOf<UQuest> Quest, const EQuestStatus Status) {
	const auto Id         = Quest.GetDefaultObject()->GetId();
	const auto FoundQuest = ActiveQuests.FindRef( Id );

	if ( FoundQuest == nullptr ) {
		UE_LOG( LogTemp, Warning, TEXT( "Quest not found" ) );
		return;
	}

	if ( FoundQuest->Status == EQuestStatus::Failed || FoundQuest->Status == EQuestStatus::Completed )
		return;

	FoundQuest->UpdateStatus( Status );

	Notify_QuestStatusChanged( FoundQuest, Status );
}

EQuestStatus UQuestComponent::GetQuestStatus(const FGuid& QuestId) const {
	const auto FoundQuest = ActiveQuests.FindRef( QuestId );
	if ( FoundQuest == nullptr )
		return EQuestStatus::NotStarted;

	return FoundQuest->Status;
}
