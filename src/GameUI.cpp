#include "GameUI.hpp"
#include <string>

Texture2D backgroundTexture;

void DrawBackground(Texture2D background)
{
	DrawTexture(background, 0, 0, WHITE);
}

void DrawPiece(Texture2D piece, Vector2 position)
{
	DrawTexture(piece, position.x, position.y, WHITE);
}

MenuOption DrawGameMenu(int screenWidth, int screenHeight)
{
	Texture2D background = LoadTexture("img/1.png");

	const char *menuOptions[] = {
		"Start New Game",
		"Load Saved Game",
		"Game Controls",
		"Game Rules",
		"levels",
		"Recorded Scores",
		"Exit"};

	int selectedOption = 0;

	while (!WindowShouldClose())
	{
		ClearBackground(RAYWHITE);

		DrawTexture(background, 0, 0, WHITE);

		for (int i = 0; i < 7; i++)
		{
			if (i == selectedOption)
			{
				DrawText(">", screenWidth / 2 - MeasureText(menuOptions[i], 20) / 2 - 20, 156 + i * 40 - 4, 30, BLUE);
				DrawText(menuOptions[i], screenWidth / 2 - MeasureText(menuOptions[i], 20) / 2, 156 + i * 40, 20, RED);
			}
			else
			{
				DrawText(menuOptions[i], screenWidth / 2 - MeasureText(menuOptions[i], 20) / 2, 156 + i * 40, 20, BLACK);
			}
		}

		if (IsKeyPressed(KEY_UP))
		{
			selectedOption--;
			if (selectedOption < 0)
				selectedOption = 6;
		}
		else if (IsKeyPressed(KEY_DOWN))
		{
			selectedOption++;
			if (selectedOption > 6)
				selectedOption = 0;
		}
		else if (IsKeyPressed(KEY_ENTER))
		{
			UnloadTexture(background);
			UnloadTexture(background);
			EndDrawing();
			return static_cast<MenuOption>(selectedOption);
		}
		EndDrawing();
	}
	UnloadTexture(background);
	return EXIT;
}

void playGame(Plateau *plateau)
{
	Texture2D pieces[4][4];
	Texture2D background = LoadTexture("img/BackgroundPlateau5.png");
	initializeTextures(pieces);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawBackground(background);
		Node *temp = plateau->getNodes();
		int k = 1;
		DrawText(TextFormat("%d", plateau->getScore()), 830, 320, 40, WHITE);
		DrawPiece(pieces[plateau->getNextPieceToInsert()->getColor()][plateau->getNextPieceToInsert()->getForm()], {470, 260});
		if (plateau->getSize() <= 10)
			DrawText(TextFormat("%d", plateau->getSize()), 180, 320, 40, WHITE);
		else
			DrawText(TextFormat("%d", plateau->getSize()), 180, 320, 40, RED);
		if (plateau->getNodes())
		{
			do
			{
				temp = temp->getNextNode();
				DrawPiece(pieces[temp->getPiece()->getColor()][temp->getPiece()->getForm()], {float(k * 58), 368});
				k++;
			} while (temp != plateau->getNodes());
		}
		EndDrawing();
		bool isRightSideUplet = false;
		bool isLeftSideUplet = false;
		int key = GetKeyPressed();
		switch (key)
		{
		case KEY_LEFT:
			plateau->insertNodeToSide(Side::LEFT);
			isLeftSideUplet = plateau->checkSideUplet(Side::LEFT);
			if (isLeftSideUplet)
			{
				plateau->deleteSideUplet(Side::LEFT);
				plateau->increaseScore(plateau->getUpletSize() - 1);
			}
			break;
		case KEY_RIGHT:
			plateau->insertNodeToSide(Side::RIGHT);
			isLeftSideUplet = plateau->checkSideUplet(Side::RIGHT);
			if (isLeftSideUplet)
			{
				plateau->deleteSideUplet(Side::RIGHT);
				plateau->increaseScore(plateau->getUpletSize() - 1);
			}
			break;

		case KEY_Q:
			goto unload;
		default:
			break;
		}
	}
unload:
	UnloadTexture(background);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			UnloadTexture(pieces[i][j]);
		}
	}
}

void initializeTextures(Texture2D pieces[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			char filename[20];
			sprintf(filename, "img/%d%d.png", i, j);
			pieces[i][j] = LoadTexture(filename);
		}
	}
}

DifficultyLevel DrawDifficultyMenu(int screenWidth, int screenHeight)
{
	Texture2D background = LoadTexture("img/1.png");
	DifficultyLevel selectedLevel = EASY;
	int menuItemHeight = 80;
	int menuPosY = (screenHeight - menuItemHeight * 3) / 2 + 30;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawBackground(background);

		DrawText("EASY", (screenWidth - MeasureText("EASY", 20)) / 2, menuPosY, 20, selectedLevel == EASY ? RED : BLACK);
		DrawText("MEDIUM", (screenWidth - MeasureText("MEDIUM", 20)) / 2, menuPosY + menuItemHeight, 20, selectedLevel == MEDIUM ? RED : BLACK);
		DrawText("HARD", (screenWidth - MeasureText("HARD", 20)) / 2, menuPosY + menuItemHeight * 2, 20, selectedLevel == HARD ? RED : BLACK);

		if (IsKeyPressed(KEY_DOWN))
		{
			selectedLevel = (selectedLevel == HARD) ? EASY : (DifficultyLevel)(selectedLevel + 1);
		}
		else if (IsKeyPressed(KEY_UP))
		{
			selectedLevel = (selectedLevel == EASY) ? HARD : (DifficultyLevel)(selectedLevel - 1);
		}
		else if (IsKeyPressed(KEY_ENTER))
		{
			EndDrawing();
			return selectedLevel;
		}
		EndDrawing();
	}
	return selectedLevel;
}