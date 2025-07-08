// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#include "QuestItemBase.h"

UQuestItemBase::UQuestItemBase() {
	Id            = FGuid::NewGuid();
	Name      = FText::FromString( TEXT( "Name" ) );
	GameplayText  = FText::FromString( TEXT( "Gameplay" ) );
	Icon          = nullptr;
}

#if WITH_EDITOR
void UQuestItemBase::PostDuplicate(bool bDuplicateForPIE) {
	UObject::PostDuplicate( bDuplicateForPIE );

	Id = FGuid::NewGuid();
}

#endif
