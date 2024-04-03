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
    RECORDED_SCORES,
    EXIT
};
MenuOption DrawGameMenu(int screenWidth, int screenHeight);
void DrawBackground(Texture2D background);
void printPlateau(Plateau &plateau);
void DrawPiece(Texture2D piece, Vector2 position);
void printPlateau(Plateau &plateau);
void playGame(Plateau *plateau);
void initializeTextures(Texture2D pieces[4][4]);
#endif