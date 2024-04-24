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

	Side side;

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
		if (plateau->getShiftTentetives() < 6 && plateau->getSize() < plateau->getMaxSize())
		{
			plateau->setShiftTentetives(6);
		}
		int key = GetKeyPressed();
		switch (key)
		{
		case KEY_LEFT:
			side = Side::LEFT;
			plateau->insertNode(side);
			break;
		case KEY_RIGHT:
			side = Side::RIGHT;
			plateau->insertNode(side);
			break;
		case KEY_S:
			plateau->shiftByForm(Form::SQUARE);
			break;
		case KEY_D:
			plateau->shiftByForm(Form::DIAMOND);
			break;
		case KEY_T:
			plateau->shiftByForm(Form::TRIANGLE);
			break;
		case KEY_C:
			plateau->shiftByForm(Form::CIRCLE);
			break;
		case KEY_R:
			plateau->shiftByColor(_Color::_RED);
			break;
		case KEY_G:
			plateau->shiftByColor(_Color::_GREEN);
			break;
		case KEY_B:
			plateau->shiftByColor(_Color::_BLUE);
			break;
		case KEY_Y:
			plateau->shiftByColor(_Color::_YELLOW);
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
		if (IsKeyPressed(KEY_Q))
		{
			EndDrawing();
			return MEDIUM;
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
		if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Q))
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
		if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Q))
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
void drawControls()
{
	const int screenWidth = 1000;
	const int screenHeight = 500;
	const int fontSize = 20;
	const int lineHeight = 30;

	const char *controls[] = {
		"  - Use Left and Right arrow keys to insert the next piece",
		"  - Press B to shift by blue color",
		"  - Press G to shift by green color",
		"  - Press R to shift by red color",
		"  - Press Y to shift by yellow color",
		"  - Press C to shift by circle form",
		"  - Press S to shift by square form",
		"  - Press T to shift by triangle form",
		"  - Press D to shift by diamond form"};

	while (!WindowShouldClose())
	{
		int posY = (screenHeight - (sizeof(controls) / sizeof(controls[0])) * lineHeight) / 2;
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText("Controls", 100, posY, fontSize, RED);
		posY += lineHeight;

		for (const auto &control : controls)
		{
			DrawText(control, 100, posY, fontSize, BLACK);
			posY += lineHeight;
		}

		if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Q))
		{
			EndDrawing();
			return;
		}
		EndDrawing();
	}
}
void drawRules()
{
	const int screenWidth = 1000;
	const int screenHeight = 500;
	const int fontSize = 20;
	const int lineHeight = 30;
	const int maxLinesPerPage = (screenHeight - 100) / lineHeight; // Calculate max lines per page based on screen height

	const char *controls[] = {
		"The goal of the game is to create uplets of shapes or colors",
		"(square, triangle, diamond, circle)(red, green, yellow, blue).",
		"Each uplet you create, earns you points. The number of points ",
		"you earn depends on the difficulty level you choose.",
		"Easy:",
		"Uplet size: 2",
		"Maximum pieces on the plateau: 6",
		"Points awarded per uplet: 4",
		"Medium:",
		"Uplet size: 3",
		"Maximum pieces on the plateau: 10",
		"Points awarded per uplet: 8",
		"Hard:",
		"Uplet size: 4",
		"Maximum pieces on the plateau: 10",
		"Points awarded per uplet: 8",
		"Once you reach the maximum size of the plateau, you can only shift the pieces six times.",
		"If you fail to create any uplets within these shifts, the game will end."};

	int scrollPosition = 0;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		// Draw title
		DrawText("Rules", 50, 50, fontSize, RED);

		// Draw controls within the visible portion of the screen
		int posY = 100;
		for (int i = scrollPosition; i < scrollPosition + maxLinesPerPage && i < sizeof(controls) / sizeof(controls[0]); ++i)
		{
			DrawText(controls[i], 50, posY, fontSize, BLACK);
			posY += lineHeight;
		}

		if (IsKeyDown(KEY_DOWN) && scrollPosition + maxLinesPerPage < sizeof(controls) / sizeof(controls[0]))
		{
			scrollPosition++;
		}
		if (IsKeyDown(KEY_UP) && scrollPosition > 0)
		{
			scrollPosition--;
		}
		if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Q))
		{
			EndDrawing();
			return;
		}
		EndDrawing();
	}
}

void endPlayGame(Plateau *plateau)
{
}
