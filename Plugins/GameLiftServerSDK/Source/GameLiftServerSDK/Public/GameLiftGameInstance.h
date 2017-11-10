//Copyright 2016 davevillz, https://github.com/davevill
#pragma once

#include "GameLiftServerSDK.h"
#include "Engine/GameInstance.h"
#include "GameLiftGameInstance.generated.h"

UCLASS()
class GAMELIFTSERVERSDK_API UGameLiftGameInstance : public UGameInstance
{
	GENERATED_UCLASS_BODY()

	UPROPERTY()
	class UGameLiftManager* GameLiftManager;

public:

	virtual void Init() override;
	virtual void Shutdown() override;

};
