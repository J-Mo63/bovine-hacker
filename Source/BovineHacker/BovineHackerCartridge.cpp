// Fill out your copyright notice in the Description page of Project Settings.
#include "BovineHackerCartridge.h"

void UBovineHackerCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
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

    if (--Lives > 0)
    {
        PrintLine(TEXT("Wrong, try again."));
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
    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    bGameOver = false;

    // Display text intro
    PrintLine(TEXT("Ok, good you're here.\nWe have to hack into these cows come on!"));
    PrintLine(TEXT("Come on, take a guess, quick!\nIt's %i characters long."), HiddenWord.Len());
}

void UBovineHackerCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Hit enter to play again."));
}