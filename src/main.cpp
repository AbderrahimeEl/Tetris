#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "../include/GameUI.hpp"

#include "../include/Plateau.hpp"

int main(void)
{

	std::cout << "ok";
	const int screenWidth = 1000;
	const int screenHeight = 500;

	InitWindow(screenWidth, screenHeight, "Add Picture Example");

	Plateau *plateau = new Plateau(15);
	plateau->LoadPlateauFromFile("game.txt");
	MenuOption selectedOption = DrawGameMenu(screenWidth, screenHeight);
	switch (selectedOption)
	{
	case START_GAME:
	{
		playGame(plateau);
		CloseWindow();

		return 0;
	}
	}
}