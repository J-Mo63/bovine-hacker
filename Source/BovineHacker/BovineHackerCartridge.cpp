// Fill out your copyright notice in the Description page of Project Settings.
#include "BovineHackerCartridge.h"

void UBovineHackerCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Ok, good you're here.\nWe have to hack into these cows come on!"));
    PrintLine(TEXT("Come on, hit enter, quick!"));
}

void UBovineHackerCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    FString HiddenWord = TEXT("cake");
    PrintLine(Input);
}
