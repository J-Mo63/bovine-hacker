// Fill out your copyright notice in the Description page of Project Settings.
#include "BovineHackerCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBovineHackerCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Retrieve all words from files and filter into valid items
    TArray<FString> AllWords;
    FFileHelper::LoadFileToStringArray(AllWords,
            *(FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt")));
    Isograms = GetValidWords(AllWords);

    // Set up the game
    SetupGame();
}

void UBovineHackerCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }
}

void UBovineHackerCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have hacked into the cow-mainframe."));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i characters long."), HiddenWord.Len());
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("That isn't an isogram!"));
        return;
    }

    if (--Lives > 0)
    {
        // Get number of correct letters
        FCorrectCount CorrectCount;
        PopulateCorrectCount(Guess, CorrectCount);

        // Provide player feedback
        PrintLine(TEXT("Wrong, try again."));
        PrintLine(TEXT("%i letters are correct and in the right spot."), CorrectCount.Position);
        PrintLine(TEXT("%i letters are correct and in the wrong spot."), CorrectCount.Letter);
        PrintLine(TEXT("You have %i lives left."), Lives);
        return;
    }
    else
    {
        PrintLine(TEXT("You're out of lives - all is lost."));
        EndGame();
    }
}

void UBovineHackerCartridge::SetupGame()
{
    // Set up fields
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    // Display text intro
    PrintLine(TEXT("Ok, good you're here.\nWe have to hack into these cows come on!"));
    PrintLine(TEXT("Come on, take a guess, quick!\nIt's %i characters long."), HiddenWord.Len());
    PrintLine(TEXT("Aaaand there's only %i possible words."), Isograms.Num());
}

void UBovineHackerCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Hit enter to play again."));
}

bool UBovineHackerCartridge::IsIsogram(const FString& Word) const
{
    for (int32 I = 0, J = I + 1; J < Word.Len(); J++)
    {
        if (Word[I] == Word[J])
        {
            return false;
        }
        else if (J == Word.Len() - 1)
        {
            J = (I++) + 1;
        }
    }
    return true;
}

TArray<FString> UBovineHackerCartridge::GetValidWords(const TArray<FString> Words) const
{
    TArray<FString> ValidWords;
    for (FString Word : Words)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}

void UBovineHackerCartridge::PopulateCorrectCount(const FString& Word, FCorrectCount& CorrectCount) const
{
    for (int32 I = 0; I < Word.Len(); I++)
    {
        if (Word[I] == HiddenWord[I])
        {
            CorrectCount.Position++;
            continue;
        }

        for (int32 J = 0; J < Word.Len(); J++)
        {
            if (Word[I] == HiddenWord[J])
            {
                CorrectCount.Letter++;
                break;
            }
        }
    }
}