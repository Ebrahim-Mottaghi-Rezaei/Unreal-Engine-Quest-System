// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#include "Structs.h"

FBaseStruct::FBaseStruct() {}

FString FBaseStruct::ToString() {
	return TEXT( "BaseStruct" );
}

FQuestInfo::FQuestInfo() {
	Id          = FGuid::NewGuid();
	Name        = FText::FromString( "Name" );
	Description = FText::FromString( "Description" );
}

FQuestCondition::FQuestCondition() {
	Item  = nullptr;
	Count = 1;
}
