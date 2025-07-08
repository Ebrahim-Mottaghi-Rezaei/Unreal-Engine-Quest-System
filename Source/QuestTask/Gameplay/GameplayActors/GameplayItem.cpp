// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#include "GameplayItem.h"

// Sets default values
AGameplayItem::AGameplayItem() {
	PrimaryActorTick.bCanEverTick          = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AGameplayItem::BeginPlay() {
	Super::BeginPlay();
}
