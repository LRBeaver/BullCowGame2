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
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

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

	std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//std::cout << MaxTries << std::endl;
	// loop for the number of turns asking for guesses

	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	//for (int32 count = 1; count <= MaxTries; count++) // TODO change from FOR to WHILE loop once we are validating tries
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// print number of bulls and cows
		std::cout << " Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	// TODO summarise game
	PrintGameSummary();

	return;
}

// loop continuakly until the user gives a valid guess

FText GetValidGuess()  
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";

		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess); 	// submit valid guess to the game
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);  // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "\nDo you want to play again with the same hidden word(y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	//std::cout << "Is it y? " << (Response[0] == 'y' || 'Y');


	return (Response[0] == 'y') || (Response[0] == 'Y');
	std::cout << std::endl;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN! \n ";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}