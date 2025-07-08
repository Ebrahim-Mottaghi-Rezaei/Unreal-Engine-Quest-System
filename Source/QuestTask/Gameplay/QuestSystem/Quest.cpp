// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#include "Quest.h"
#include "Kismet/GameplayStatics.h"
#include "QuestTask/Components/QuestComponent.h"
#include "QuestTask/Interfaces/QuestInterface.h"

UQuest::UQuest() {
	Status = EQuestStatus::NotStarted;
}

UQuest::~UQuest() {
	const auto QuestComponent = RetrieveQuestComponent();
	if ( !IsValid( QuestComponent ) )
		return;

	if ( QuestComponent->OnQuestStatusChanged.IsAlreadyBound( this, &ThisClass::OnQuestStatusChanged ) )
		QuestComponent->OnQuestStatusChanged.RemoveDynamic( this, &ThisClass::OnQuestStatusChanged );
}

void UQuest::UpdateStatus(const EQuestStatus NewStatus) {
	if ( Status == NewStatus )
		return;

	if ( Status == EQuestStatus::Active ) {
		if ( CheckIfConditionsMeet() ) {
			Notify_StatusChanged( EQuestStatus::Completed );

			return;
		}

		const auto QuestComponent = RetrieveQuestComponent();
		if ( !IsValid( QuestComponent ) )
			return;

		QuestComponent->OnQuestStatusChanged.AddDynamic( this, &ThisClass::OnQuestStatusChanged );
	}

	Status = NewStatus;
	Notify_StatusChanged( Status );
}

void UQuest::OnQuestStatusChanged(UQuest* Quest, EQuestStatus NewStatus) {
	CheckIfConditionsMeet();
}

UQuestComponent* UQuest::RetrieveQuestComponent() const {
	const auto World = GetWorld();
	if ( World == nullptr ) {
		UE_LOG( LogTemp, Warning, TEXT( "World is null" ) );
		return nullptr;
	}

	const auto PlayerController = UGameplayStatics::GetPlayerController( World, 0 );
	if ( !PlayerController ) {
		UE_LOG( LogTemp, Warning, TEXT( "PlayerController is null" ) );
		return nullptr;
	}

	return IQuestInterface::Execute_GetQuestComponent( PlayerController );
}

bool UQuest::CheckIfConditionsMeet() {
	const auto QuestComponent = RetrieveQuestComponent();
	if ( !IsValid( QuestComponent ) )
		return false;

	if ( CompleteConditions.Num() == 0 )
		return false;

	for ( const auto Condition : CompleteConditions ) {
		if ( Condition.Item == nullptr ) {
			continue;
		}
		const auto ItemId = Condition.Item.GetDefaultObject()->GetId();

		if ( QuestComponent->GetQuestStatus( ItemId ) == EQuestStatus::Failed ) {
			UpdateStatus( EQuestStatus::Failed );
			return false;
		}

		if ( QuestComponent->GetQuestStatus( ItemId ) != EQuestStatus::Completed )
			return false;
	}
	return true;
}

UWorld* UQuest::GetWorld() const {
	if ( HasAllFlags( RF_ClassDefaultObject ) )
		return nullptr;

	auto Outer = GetOuter();

	while ( Outer->IsValidLowLevelFast() ) {
		if ( UWorld* World = Outer->GetWorld() )
			return World;

		Outer = Outer->GetOuter();
	}

	return nullptr;
}
