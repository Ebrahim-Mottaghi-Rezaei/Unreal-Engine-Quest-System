// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#include "Quest.h"

#include "Conditions/QuestCondition.h"
#include "Kismet/GameplayStatics.h"
#include "QuestTask/Components/QuestComponent.h"
#include "QuestTask/Gameplay/QuestSystem/Interfaces/QuestInterface.h"

UQuest::UQuest() {
	Status = EQuestStatus::NotStarted;

	Id           = FGuid::NewGuid();
	Name         = FText::FromString( TEXT( "Name" ) );
	GameplayText = FText::FromString( TEXT( "Gameplay" ) );
	Icon         = nullptr;

	QuestComponent = nullptr;
	Condition      = nullptr;
}

UQuest::~UQuest() {
	if ( !QuestComponent.IsValid() )
		return;

	if ( QuestComponent->OnQuestStatusChanged.IsAlreadyBound( this, &ThisClass::OnQuestStatusChanged ) )
		QuestComponent->OnQuestStatusChanged.RemoveDynamic( this, &ThisClass::OnQuestStatusChanged );

	QuestComponent.Reset();
}

void UQuest::UpdateStatus(const EQuestStatus NewStatus) {
	if ( Status == NewStatus )
		return;

	if ( IsValid( Condition ) )
		if ( NewStatus == EQuestStatus::Active ) {
			if ( Condition->Evaluate_Implementation() ) {
				Notify_StatusChanged( EQuestStatus::Completed );
				return;
			}

			if ( !QuestComponent.IsValid() )
				QuestComponent = GetQuestComponent();

			QuestComponent->OnQuestStatusChanged.AddDynamic( this, &ThisClass::OnQuestStatusChanged );
		}

	Status = NewStatus;
	Notify_StatusChanged( Status );
}

void UQuest::OnQuestStatusChanged(UQuest* Quest, EQuestStatus NewStatus) {
	if ( NewStatus == EQuestStatus::Failed )
		UpdateStatus( EQuestStatus::Failed );
	else if ( Condition->Evaluate_Implementation() )
		UpdateStatus( EQuestStatus::Completed );
}

UQuestComponent* UQuest::GetQuestComponent() const {
	const auto World = GetWorld();
	if ( !IsValid( World ) ) {
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

UInventoryComponent* UQuest::GetInventoryComponent() const {
	const auto World = GetWorld();
	if ( !IsValid( World ) ) {
		UE_LOG( LogTemp, Warning, TEXT( "World is null" ) );
		return nullptr;
	}

	const auto PlayerController = UGameplayStatics::GetPlayerController( World, 0 );
	if ( !PlayerController ) {
		UE_LOG( LogTemp, Warning, TEXT( "PlayerController is null" ) );
		return nullptr;
	}

	return IQuestInterface::Execute_GetInventoryComponent( PlayerController );
}

#if WITH_EDITOR
void UQuest::PostDuplicate(bool bDuplicateForPIE) {
	UObject::PostDuplicate( bDuplicateForPIE );

	Id = FGuid::NewGuid();
}

#endif

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
