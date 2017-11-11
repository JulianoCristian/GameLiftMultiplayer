//Copyright 2016 davevillz, https://github.com/davevill
#pragma once

#include "GameLiftServerSDK.h"
#include "Object.h"
#include "Tickable.h"
#include "GameLiftTypes.h"
#include "GameFramework/OnlineReplStructs.h"
#include "GameLiftManager.generated.h"



UCLASS(Config=Game)
class GAMELIFTSERVERSDK_API UGameLiftManager : public UObject, public FTickableGameObject
{
	GENERATED_BODY()


	bool bInitialized;
	bool bGameSessionActive;


	/* Unique ID as a string to session id */
	TMap<FString, TArray<FString>> PlayerSessions;

	UPROPERTY()
	class UGameInstance* GameInstance;


	UFUNCTION()
	void RequestExit();


public:

	/** How long has the game session being active, server time */
	UPROPERTY(BlueprintReadOnly, Category="GameLift")
	float GameSessionDuration;


	UGameLiftManager();


	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override { return UObject::GetStatID(); }


	virtual class UWorld* GetWorld() const override;


	/** Must be called within the GameInstance::Init method */
	virtual void Init();

	/** Must be called within the GameInstance::Shutdown method */
	virtual void Shutdown();

	/** Called when the GameLift service receives request to start a new game session, Loading a map game mode and other settings
	  * should happend here. When the server is ready for players to connect, ActivateGameSession should be called. 
	  * 
	  * The default implementations loads the map defined in the "map" property, with max players and game mode */
	virtual void OnStartGameSession(const FGameLiftGameSession& GameSession);

	/** Called when GameLift service needs to force the server process to terminate, allowing the server process to shut down gracefully */
	virtual void OnProcessTerminate();




	/** Return true if this is running on AWS GameLift fleet */
	UFUNCTION(BlueprintPure, Category="GameLift")
	bool IsFleetInstance() const;


	/** Global getter */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get GameLift Manager", WorldContext = "WorldContextObject"), Category = "GameLift")
	static UGameLiftManager* Get(UObject* WorldContextObject);


	/** This should be called within the GameMode::PreLogin method passing both Options and ErrorMessage.
	  * it functions in the same way, if ErrorMessage is set, it means player was rejected or/and if it returns false.*/
	UFUNCTION(BlueprintCallable, Category="GameLift")
	bool AcceptPlayerSession(const FString& Options, const FUniqueNetIdRepl& UniqueNetId, FString& ErrorMessage);

	/** Should be called when a player disconnects from the server */
	UFUNCTION(BlueprintCallable, Category="GameLift")
	void RemovePlayerSession(const FUniqueNetIdRepl& UniqueId);

	/** Activates the game session */
	UFUNCTION(BlueprintCallable, Category="GameLift")
	void ActivateGameSession();

	/** Termintes the game session, ProcessEnding should be called if the server needs to be restarted, 
	  * otherwise it will inmediatly be available to host new game sessions */
	UFUNCTION(BlueprintCallable, Category="GameLift")
	void TerminateGameSession();

	/** Notifies GameLift Service that the server is imediatetly ending/exiting, this calls QuitGame internally */
	UFUNCTION(BlueprintCallable, Category="GameLift")
	void ProcessEnding();

	UFUNCTION(BlueprintCallable, Category="GameLift")
	void ProcessReady();

	UFUNCTION(BlueprintCallable, Category = "GameLift")
	void UpdatePlayerSessionCreationPolicy(EGameLiftPlayerSessionCreationPolicy Policy);
};
