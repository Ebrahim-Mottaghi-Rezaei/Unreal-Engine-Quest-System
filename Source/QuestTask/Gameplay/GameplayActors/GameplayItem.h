// Copyright Ebrahim Mottaghi Rezaei <https://www.linkedin.com/in/ebrahim-mr>. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayItem.generated.h"

class UQuestItemBase;

UCLASS()
class QUESTTASK_API AGameplayItem : public AActor {
	GENERATED_BODY()

public:
	AGameplayItem();

protected:
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Instanced, meta=(editinlinenew) )
	UQuestItemBase* Item;

	virtual void BeginPlay() override;
};
