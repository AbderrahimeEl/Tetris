#ifndef GAME_UI_HPP
#define GAME_UI_HPP
#include "Plateau.hpp"
#include <raylib.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
enum MenuOption
{
    START_GAME,
    LOAD_SAVED_GAME,
    GAME_CONTROLS,
    GAME_RULES,
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
bool IsAnyKeyPressed();
MenuOption DrawGameMenu(int screenWidth, int screenHeight);
void DrawBackground(Texture2D background);
void printPlateau(Plateau &plateau);
void DrawYouLose(int score);
void drawScores();
void DrawPiece(Texture2D piece, Vector2 position);
void printPlateau(Plateau &plateau);
void playGame(Plateau *plateau);
void initializeTextures(Texture2D pieces[4][4]);
DifficultyLevel DrawDifficultyMenu(int screenWidth, int screenHeight);
char *drawUserInput(int score);
void updateScores(const char *name, int score);
int getLastScore();
void drawControls();
void drawRules();
void endPlayGame(Plateau *plateau);
#endif