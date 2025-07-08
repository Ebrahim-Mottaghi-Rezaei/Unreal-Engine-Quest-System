// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#include "QuestTriggerBox.h"
#include "QuestTask/Components/QuestComponent.h"
#include "QuestTask/Gameplay/QuestSystem/Quest.h"
#include "QuestTask/Gameplay/QuestSystem/Interfaces/QuestInterface.h"

AQuestTriggerBox::AQuestTriggerBox() {
	PrimaryActorTick.bCanEverTick          = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Action    = EQuestTriggerVolumeAction::Add;
	NewStatus = EQuestStatus::NotStarted;
	Quest     = nullptr;
}

void AQuestTriggerBox::NotifyActorBeginOverlap(AActor* OtherActor) {
	Super::NotifyActorBeginOverlap( OtherActor );

	if ( !IsValid( OtherActor ) ) {
		UE_LOG( LogTemp, Warning, TEXT( "OtherActor is null" ) );
		return;
	}

	if ( !IsValid( Quest ) ) {
		UE_LOG( LogTemp, Warning, TEXT( "Quest is null" ) );
		return;
	}

	const auto Controller     = Cast<APawn>( OtherActor )->GetController();
	const auto QuestComponent = IQuestInterface::Execute_GetQuestComponent( Controller );
	if ( Action == EQuestTriggerVolumeAction::Add )
		QuestComponent->AddQuest( Quest );
	else
		QuestComponent->UpdateQuestStatus( Quest, NewStatus );
}
