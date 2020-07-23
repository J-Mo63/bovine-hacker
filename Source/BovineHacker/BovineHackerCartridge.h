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

    struct FCorrectCount {
        int32 Position = 0;
        int32 Letter = 0;
    };

	private:

    TArray<FString> Isograms;
    FString HiddenWord;
    int32 Lives;
    bool bGameOver;

    void SetupGame();
    TArray<FString> GetValidWords(const TArray<FString> Words) const;
    void EndGame();
    void ProcessGuess(const FString& Guess);
    bool IsIsogram(const FString& Word) const;
    void PopulateCorrectCount(const FString& Word, FCorrectCount& CorrectCount) const;
};