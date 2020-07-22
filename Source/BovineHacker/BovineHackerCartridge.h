// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BovineHackerCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BOVINEHACKER_API UBovineHackerCartridge : public UCartridge
{
	GENERATED_BODY()

	public:

	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	private:

    TArray<FString> Words;
    FString HiddenWord;
    int32 Lives;
    bool bGameOver;

    void SetupGame();
    TArray<FString> GetValidWords() const;
    void EndGame();
    void ProcessGuess(const FString& FString);
    bool IsIsogram(const FString& FString) const;
};
