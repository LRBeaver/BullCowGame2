/* 
This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // Instantiate a new game

int main()
{
	std::cout << BCGame.GetCurrentTry();
	
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;
}

void PrintIntro()
{
	// introduce the game
	// constexpr int32 WORD_LENGTH = 5;

	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << MaxTries << std::endl;
	// loop for the number of turns asking for guesses
	// TODO change from FOR to WHILE loop once we are validating tries

	for (int32 count = 1; count <= MaxTries; count++)
	{
		FText Guess = GetGuess(); // TODO make loop checking valid

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		// print number of bulls and cows
		std::cout << " Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
		//std::cout << "You guess was: " << Guess << std::endl;
		std::cout << std::endl;
	}

	// TODO summarise game
}

FText GetGuess()
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	
	// get a guess from the player
	
	std::cout << "Try " << CurrentTry << ". Enter your guess: ";
	FText Guess = "";

	std::getline(std::cin, Guess);
	return Guess;

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	//std::cout << "Is it y? " << (Response[0] == 'y' || 'Y');


	return (Response[0] == 'y') || (Response[0] == 'Y');
	std::cout << std::endl;
}
