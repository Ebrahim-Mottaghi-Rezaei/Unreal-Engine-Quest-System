// Copyright Ebrahim Mottaghi Rezaei [https://www.linkedin.com/in/ebrahim-mr/]. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Structs.generated.h"

USTRUCT( BlueprintType, Category = "DataTypes" )
struct QUESTTASK_API FBaseStruct {
	GENERATED_BODY()

public:
	virtual ~FBaseStruct() = default;

	FBaseStruct();

	virtual FString ToString();
};

USTRUCT( BlueprintType, Category = "DataTypes" )
struct QUESTTASK_API FQuestInfo : public FBaseStruct {
	GENERATED_BODY()

public:
	FQuestInfo();

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	int Id = 0;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText Name;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FText Description;
};
