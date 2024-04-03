#include "GameUI.hpp"
#include <string>

Texture2D backgroundTexture ;

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
        "Start Game",
        "Load Saved Game",
        "Game Controls",
        "Game Rules",
        "Recorded Scores",
        "Exit"};

    int selectedOption = 0;

    while (!WindowShouldClose())
    {
        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE);

        for (int i = 0; i < 6; i++)
        {
            if (i == selectedOption)
            {
                DrawText(menuOptions[i], screenWidth / 2 - MeasureText(menuOptions[i], 20) / 2, 200 + i * 40, 20, RED);
            }
            else
            {
                DrawText(menuOptions[i], screenWidth / 2 - MeasureText(menuOptions[i], 20) / 2, 200 + i * 40, 20, BLACK);
            }
        }

        if (IsKeyPressed(KEY_UP))
        {
            selectedOption--;
            if (selectedOption < 0)
                selectedOption = 5;
        }
        else if (IsKeyPressed(KEY_DOWN))
        {
            selectedOption++;
            if (selectedOption > 5)
                selectedOption = 0;
        }
        else if (IsKeyPressed(KEY_ENTER))
        {

            UnloadTexture(background);
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
	Texture2D background = LoadTexture("img/BackgroundPlateau4.png");
	initializeTextures(pieces);
	while (!WindowShouldClose())
	{
		bool isRightSideUplet = false;
		bool isLeftSideUplet = false;
		int key = GetKeyPressed();
		// std::cout << "ok";
		switch (key)
		{
		case KEY_LEFT:
			plateau->insertNodeToSide(Side::LEFT);
			isLeftSideUplet = plateau->checkSideUplet(Side::LEFT);
			if (isLeftSideUplet)
			{
				plateau->deleteSideUplet(Side::LEFT);
			}
			break;
		case KEY_RIGHT:
			plateau->insertNodeToSide(Side::RIGHT);
			isLeftSideUplet = plateau->checkSideUplet(Side::RIGHT);
			if (isLeftSideUplet)
			{
				plateau->deleteSideUplet(Side::RIGHT);
			}
			// plateau->savePlateauToFile("game.txt");
			break;
		default:
			break;
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawBackground(background);
		Node *temp = plateau->getNodes();
		int k = 1;
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
	}
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