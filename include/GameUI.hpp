#ifndef GAME_UI8HPP
#define GAME8UI8HPP
#include "Plateau.hpp"
#include <raylib.h>
#include <string>
enum MenuOption
{
    START_GAME,
    LOAD_SAVED_GAME,
    GAME_RULES,
    GAME_CONTROLS,
    LEVEL,
    RECORDED_SCORES,
    EXIT
};
enum DifficultyLevel
{
    EASY = 1,
    MEDIUM = 2,
    HARD = 3
};

MenuOption DrawGameMenu(int screenWidth, int screenHeight);
void DrawBackground(Texture2D background);
void printPlateau(Plateau &plateau);
void DrawPiece(Texture2D piece, Vector2 position);
void printPlateau(Plateau &plateau);
void playGame(Plateau *plateau);
void initializeTextures(Texture2D pieces[4][4]);
DifficultyLevel DrawDifficultyMenu(int screenWidth, int screenHeight);
#endif