#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <array>
using namespace std;

int gameRounds = 0;
int computerWonTimes = 0;
int playerOwnTimes = 0;
int drawTimes = 0;

int NumberOfRounds()
{
	int Number = 0;
	do
	{
		cout << "How Many Rounds 1 to 10: ";
		cin >> Number;

	} while (Number <= 0);

	return Number;
}

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;

	return randNum;
}

string Taps()
{
	return "\t\t";
}

enum enChoices { Stone = 1, Paper = 2, Scissors = 3 };

struct stRoundInfo
{
	string UserChoice;
	string ComputerChoice;
	string RoundWinner;
};

struct stPlayers
{
	string Player1 = "Player1";
	string Computer = "Computer";
};

struct stGameInfo
{
	int GameRounds = 0;
	int PlayerOwnTimes = computerWonTimes;
	int ComputerWonTimes = playerOwnTimes;
	int DrawTimes = drawTimes;
	string FinalWinner = "";
};

enChoices ReadUserChoice()
{
	int choice = 0;
	do
	{
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
		cin >> choice;

	} while (choice < 1 || choice > 3);

	return (enChoices)choice;
}

enChoices ReadComputerChoice()
{
	enChoices Choices[3] = { enChoices::Stone, enChoices::Paper, enChoices::Scissors };

	return Choices[RandomNumber(0, 2)];
}

void ScreenColor(string Winner)
{
	stPlayers Player;

	if (Winner == Player.Player1)
	{
		system("color 2F");
	}
	else if (Winner == Player.Computer)
	{
		cout << "\a";
		system("color 4F");
	}
	else
	{
		system("color 6F");
	}
}

enChoices GameRolls(enChoices UserChoice, enChoices ComputerChoice)
{

	if (UserChoice == enChoices::Stone && ComputerChoice == enChoices::Stone)
		return enChoices::Stone;
	else if (UserChoice == enChoices::Stone && ComputerChoice == enChoices::Paper)
		return enChoices::Paper;
	else if (UserChoice == enChoices::Stone && ComputerChoice == enChoices::Scissors)
		return enChoices::Stone;
	else if (UserChoice == enChoices::Paper && ComputerChoice == enChoices::Stone)
		return enChoices::Paper;
	else if (UserChoice == enChoices::Paper && ComputerChoice == enChoices::Paper)
		return enChoices::Paper;
	else if (UserChoice == enChoices::Paper && ComputerChoice == enChoices::Scissors)
		return enChoices::Scissors;
	else if (UserChoice == enChoices::Scissors && ComputerChoice == enChoices::Stone)
		return enChoices::Stone;
	else if (UserChoice == enChoices::Scissors && ComputerChoice == enChoices::Paper)
		return enChoices::Scissors;
	else if (UserChoice == enChoices::Scissors && ComputerChoice == enChoices::Scissors)
		return enChoices::Scissors;
}

string RoundWinner(enChoices UserChoice, enChoices ComputerChoice)
{
	stPlayers Players;
	enChoices Choice = GameRolls(UserChoice, ComputerChoice);

	if (UserChoice == Choice && ComputerChoice == Choice)
	{
		return "No Winner";
	}
	else if (UserChoice == Choice)
	{
		return Players.Player1;
	}
	else
	{
		return Players.Computer;
	}

}

string FinalWinner()
{
	stPlayers Player;

	if (playerOwnTimes > computerWonTimes)
		return Player.Player1;
	else if (playerOwnTimes < computerWonTimes)
		return Player.Computer;
	else
		return "No Winner";
}

void FillRoundInfo(enChoices UserChoice, enChoices ComputerChoice, stRoundInfo& RoundInfo)
{
	stPlayers Player;
	string roundWinner = RoundWinner(UserChoice, ComputerChoice);

	RoundInfo.RoundWinner = roundWinner;

	switch (UserChoice)
	{
	case enChoices::Stone:
		RoundInfo.UserChoice = "Stone";
		break;
	case enChoices::Paper:
		RoundInfo.UserChoice = "Paper";
		break;
	case enChoices::Scissors:
		RoundInfo.UserChoice = "Scissors";
		break;
	}

	switch (ComputerChoice)
	{
	case enChoices::Stone:
		RoundInfo.ComputerChoice = "Stone";
		break;
	case enChoices::Paper:
		RoundInfo.ComputerChoice = "Paper";
		break;
	case enChoices::Scissors:
		RoundInfo.ComputerChoice = "Scissors";
		break;
	}

}

void PrintRoundResult(stRoundInfo RoundInfo, int RoundNumber)
{

	cout << "\n_______________ Round [" << RoundNumber << "] _______________\n\n";

	cout << "Player1 Choice : " << RoundInfo.UserChoice << endl;
	cout << "Computer Choice: " << RoundInfo.ComputerChoice << endl;
	cout << "Round Winner   : " << RoundInfo.RoundWinner << endl;

	cout << "_________________________________________\n\n";

	ScreenColor(RoundInfo.RoundWinner);

}

void GetRoundResult(string RoundWinner, int& GameRounds)
{
	stPlayers Player;

	gameRounds = GameRounds;

	if (RoundWinner == Player.Player1)
		playerOwnTimes++;
	else if (RoundWinner == Player.Computer)
		computerWonTimes++;
	else
		drawTimes++;
}

stGameInfo GetFinalResult()
{
	stGameInfo GameInfo;

	GameInfo.GameRounds = gameRounds;
	GameInfo.PlayerOwnTimes = playerOwnTimes;
	GameInfo.ComputerWonTimes = computerWonTimes;
	GameInfo.DrawTimes = drawTimes;
	GameInfo.FinalWinner = FinalWinner();

	return GameInfo;
}

void StartRound(int RoundNumbers, int RoundNumber)
{
	enChoices UserChoice = ReadUserChoice();
	enChoices ComputerChoice = ReadComputerChoice();
	stRoundInfo RoundInfo;

	string roundWinner = RoundWinner(UserChoice, ComputerChoice);

	FillRoundInfo(UserChoice, ComputerChoice, RoundInfo);

	PrintRoundResult(RoundInfo, RoundNumber);

	GetRoundResult(roundWinner, RoundNumbers);
}

bool IsValidInput(char Input)
{
	char Inp = Input;

	switch (Inp)
	{
	case 'N':
		return true;
		break;
	case 'n':
		return true;
		break;
	case 'Y':
		return true;
		break;
	case 'y':
		return true;
		break;
	default:
		return false;
		break;
	}
}

bool PlayAgain()
{
	char playAgain = 'N';

	do
	{
		cout << Taps() << "Do you want to play again? Y/N? ";
		cin >> playAgain;
		cout << endl;

	} while (!IsValidInput(playAgain));

	if (playAgain == 'N' || playAgain == 'n')
		return false;
	else
		return true;

}

void GameOver()
{
	stGameInfo GameInfo = GetFinalResult();

	cout << Taps() << "_________________________________________________\n\n";

	cout << Taps() << Taps() << "+++ G a m e  O v e r +++" << endl;

	cout << Taps() << "_________________________________________________\n\n";

	cout << Taps() << "____________________ [Game Results]______________\n\n";

	cout << Taps() << "Game Rounds       : " << GameInfo.GameRounds << endl;
	cout << Taps() << "Player1 won times : " << GameInfo.PlayerOwnTimes << endl;
	cout << Taps() << "Computer won times: " << GameInfo.ComputerWonTimes << endl;
	cout << Taps() << "Draw times        : " << GameInfo.DrawTimes << endl;
	cout << Taps() << "Final Winner      : [" << GameInfo.FinalWinner << "]" << endl;

	cout << Taps() << "__________________________________________________\n\n";

	ScreenColor(GameInfo.FinalWinner);

}

void StartRounds()
{
	int RoundsNumber = NumberOfRounds();

	for (int i = 1; i <= RoundsNumber; i++)
	{
		cout << "\nRound [" << i << "] begins: \n";

		StartRound(RoundsNumber, i);
	}

	GameOver();
}

void ResetGame()
{
	playerOwnTimes = 0;
	computerWonTimes = 0;
	drawTimes = 0;
	system("cls");
	system("color F");
}

void StartGame()
{
	do
	{
		ResetGame();
		StartRounds();

	} while (PlayAgain());

}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}

