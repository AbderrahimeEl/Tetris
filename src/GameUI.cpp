#include "../include/GameUI.hpp"
int minScore = getLastScore();

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

		if (plateau->getSize() == plateau->getMaxSize())
		{
			DrawText(TextFormat("R_SHIFTS :"), 700, 180, 30, WHITE);
			DrawText(TextFormat("%d", plateau->getShiftTentetives()), 890, 180, 30, RED);
		}
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
		case KEY_LEFT_SHIFT:
			if (plateau->getSize() == plateau->getMaxSize())
			{
				plateau->setShiftTentetives(plateau->getShiftTentetives() - 1);
			}
			if (plateau->getSize() == plateau->getMaxSize() && plateau->getShiftTentetives() == 0)
			{
				if (plateau->getScore() <= minScore)
					DrawYouLose(plateau->getScore());
				else
				{
					char *name = drawUserInput(plateau->getScore());
					updateScores(name, plateau->getScore());
				}
				goto unload;
			}
			break;

		case KEY_Q:
			if (plateau->getScore() > minScore)
			{
				char *name = drawUserInput(plateau->getScore());
				updateScores(name, plateau->getScore());
			}
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

void DrawYouLose(int score)
{
	Texture2D background = LoadTexture("img/1.png");
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("YOU LOSE", (1000 - MeasureText("YOU LOSE", 40)) / 2, 150, 40, RED);
		DrawText(TextFormat("YOUR SCORE %d", score), (1000 - MeasureText(TextFormat("YOUR SCORE %d", score), 40)) / 2, 250, 40, BLACK);
		DrawText("Press enter to return", (1000 - MeasureText("Press enter to return", 20)) / 2, 400, 20, BLACK);
		if (IsKeyPressed(KEY_ENTER))
		{
			EndDrawing();
			UnloadTexture(background);
			return;
		}
		EndDrawing();
	}
}
char *drawUserInput(int score)
{
	const int MAX_INPUT_CHARS = 15;
	char *name = (char *)malloc((MAX_INPUT_CHARS + 1) * sizeof(char));
	strcpy(name, "");

	int letterCount = 0;

	int screenWidth = 1000;
	int screenHeight = 500;

	Rectangle textBox = {200, 290, 600, 50};
	bool mouseOnText = false;
	bool resetChar = true;
	int framesCounter = 0;
	// ClearInputBuffer();
	SetTargetFPS(10);
	while (!WindowShouldClose())
	{
		int key = GetCharPressed();
		while (key > 0)
		{
			if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
			{
				name[letterCount] = (char)key;
				name[letterCount + 1] = '\0';
				letterCount++;
			}

			key = GetCharPressed();
		}

		if (IsKeyPressed(KEY_BACKSPACE))
		{
			letterCount--;
			if (letterCount < 0)
				letterCount = 0;
			name[letterCount] = '\0';
		}
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText("Congratulations!", (1000 - MeasureText("Congratulations!", 30)) / 2, 100, 30, RED);
		DrawText("Your score is in the top 10!", (1000 - MeasureText("Your score is in the top 10!", 30)) / 2, 160, 30, BLACK);
		DrawText(TextFormat("SCORE : %d", score), (1000 - MeasureText(TextFormat("SCORE : %d", score), 30)) / 2, 220, 30, BLACK);
		DrawText("Enter your name: ", 220, 270, 20, LIGHTGRAY);

		DrawRectangleRec(textBox, LIGHTGRAY);
		if (mouseOnText)
			DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
		else
			DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

		DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

		if (mouseOnText)
		{
			if (letterCount < MAX_INPUT_CHARS)
			{
				if (((framesCounter / 20) % 2) == 0)
					DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
			}
			else
				DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
		}
		EndDrawing();
		if (IsKeyPressed(KEY_ENTER))
		{
			EndDrawing();
			return name; // Return the name when Enter is pressed
		}
	}
	return name;
}

bool IsAnyKeyPressed()
{
	bool keyPressed = false;
	int key = GetKeyPressed();

	if ((key >= 32) && (key <= 126))
		keyPressed = true;

	return keyPressed;
}

void updateScores(const char *name, int score)
{
	std::ifstream infile("data/scores.txt");
	std::vector<std::pair<std::string, int>> scores;
	std::string tempName;
	int tempScore;

	while (infile >> tempName >> tempScore)
	{
		scores.push_back({tempName, tempScore});
	}
	infile.close();

	scores.push_back({name, score});

	std::sort(scores.begin(), scores.end(),
			  [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
			  {
				  return a.second > b.second;
			  });

	if (scores.size() > 10)
	{
		scores.resize(10);
		minScore = scores[9].second;
	}

	std::ofstream outfile("data/scores.txt");
	for (const auto &s : scores)
	{
		outfile << s.first << " " << s.second << std::endl;
	}
	outfile.close();
}

void drawScores()
{
	std::ifstream infile("data/scores.txt");
	std::vector<std::pair<std::string, int>> scores;
	std::string tempName;
	int tempScore;
	while (infile >> tempName >> tempScore)
	{
		scores.push_back({tempName, tempScore});
	}
	infile.close();
	while (!WindowShouldClose())
	{
		int y = 70;
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("SCORE     PLAYER", 390, y, 20, RED);
		y += 55;
		for (const auto &s : scores)
		{
			DrawText((std::to_string(s.second) + "   -   " + s.first).c_str(), 400, y, 20, BLACK);
			y += 30;
		}
		if (IsKeyPressed(KEY_ENTER))
		{
			EndDrawing();
			return;
		}
		EndDrawing();
	}
}

int getLastScore()
{
	std::ifstream file("data/scores.txt");
	std::string line;
	int lastScore = 0;

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			std::string scoreStr = line.substr(line.size() - 3, 3);
			int score = std::stoi(scoreStr);
			lastScore = score;
		}
		file.close();
	}
	return lastScore;
}