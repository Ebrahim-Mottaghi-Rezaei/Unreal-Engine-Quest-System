// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#include "Quest.h"

UQuest::UQuest() {
	Status = EQuestStatus::NotStarted;
}

void UQuest::UpdateStatus(EQuestStatus NewStatus) {
	if ( Status == NewStatus )
		return;

	Status = NewStatus;
	Notify_StatusChanged( Status );
}

UWorld* UQuest::GetWorld() const {
	if ( HasAllFlags( RF_ClassDefaultObject ) )
		return nullptr;

	auto Outer = GetOuter();

	while ( Outer ) {
		if ( UWorld* World = Outer->GetWorld() )
			return World;

		Outer = Outer->GetOuter();
	}

	return nullptr;
}
