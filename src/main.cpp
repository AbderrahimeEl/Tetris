#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "../include/GameUI.hpp"
#include "../include/Plateau.hpp"

int main(void)
{
	const int screenWidth = 1000;
	const int screenHeight = 500;

	InitWindow(screenWidth, screenHeight, "TETRIS");

	Plateau *plateau = new Plateau(15);
	MenuOption selectedOption;
	do
	{
		selectedOption = DrawGameMenu(screenWidth, screenHeight);
		switch (selectedOption)
		{
		case START_GAME:
		{
			playGame(plateau);
			plateau->savePlateauToFile("data/game.txt");
			break;
		}
		case LOAD_SAVED_GAME:
		{
			plateau->LoadPlateauFromFile("data/game.txt");
			playGame(plateau);
			plateau->savePlateauToFile("data/game.txt");
			break;
		}
		case LEVEL:
		{
			DifficultyLevel level = DrawDifficultyMenu(screenWidth, screenHeight);
			plateau->setUpletSize(level + 1);
			break;
		}
		case RECORDED_SCORES:
		{
			drawScores();
			break;
		}
		case GAME_CONTROLS:
		{
			drawControls();
			break;
		}
		case GAME_RULES:
		{
			drawRules();
			break;
		}
		}
	} while (selectedOption != EXIT);
	CloseWindow();
}