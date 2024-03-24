﻿#include <iostream>
#include <stdlib.h>
#include <termios.h>
#define STDIN_FILENO 0


#include "../include/Plateau.hpp"


// Keyboard key numbers
#define LEFT_ARROW_KEY 68
#define RIGHT_ARROW_KEY 67

// Colors
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"

// Function declarations
void printPlateau(Plateau& plateau, bool printDetails);
void printPiece(Piece piece);
int waitForKeyHit();
std::string formsPointerChecker(Plateau& plateau, Form form);
std::string colorsPointerChecker(Plateau& plateau, Color color);
void setupLinuxTerminalSettings(termios& t);
void restoreLinuxTerminalSettings(termios& t);

int main()
{
	struct termios t;
	setupLinuxTerminalSettings(t);

	Plateau plateau(15);
	bool displayDiagnosticInfo = false;

	std::cout << "Press left and right arrow keys to insert the next piece" << std::endl << std::endl;

	while (true)
	{
		printPlateau(plateau, displayDiagnosticInfo);

		int key = waitForKeyHit();
		std::cout << std::endl;

		bool isRightSideUplet = false;
		bool isLeftSideUplet = false;

		switch (key)
		{
		case LEFT_ARROW_KEY:
			plateau.insertNodeToSide(Side::LEFT);
			isLeftSideUplet = plateau.checkSideUplet(Side::LEFT);

			if (isLeftSideUplet)
			{
				plateau.deleteSideUplet(Side::LEFT);
			}

			if (displayDiagnosticInfo)
			{
				isLeftSideUplet ? std::cout << " L.U | " : std::cout << "!L.U | ";
			}

			break;

		case RIGHT_ARROW_KEY:
			plateau.insertNodeToSide(Side::RIGHT);

			isRightSideUplet = plateau.checkSideUplet(Side::RIGHT);

			if (isRightSideUplet)
			{
				plateau.deleteSideUplet(Side::RIGHT);
			}

			if (displayDiagnosticInfo)
			{
				isRightSideUplet ? std::cout << " R.U | " : std::cout << "!R.U | ";
			}

			break;

		default:
			break;
		}
	}

		restoreLinuxTerminalSettings(t);
}

void printPlateau(Plateau& plateau, bool printDetails) {
	if (printDetails)
	{
		std::cout << "(C: " << plateau.getForms()[static_cast<int>(Form::CIRCLE)].getNumberOfElements() << "; " << formsPointerChecker(plateau, Form::CIRCLE) << ")|";
		std::cout << "(S: " << plateau.getForms()[static_cast<int>(Form::SQUARE)].getNumberOfElements() << "; " << formsPointerChecker(plateau, Form::SQUARE) << ")|";
		std::cout << "(T: " << plateau.getForms()[static_cast<int>(Form::TRIANGLE)].getNumberOfElements() << "; " << formsPointerChecker(plateau, Form::TRIANGLE) << ")|";
		std::cout << "(R: " << plateau.getForms()[static_cast<int>(Form::RHOMBUS)].getNumberOfElements() << "; " << formsPointerChecker(plateau, Form::RHOMBUS) << ") || ";

		std::cout << "(" << ANSI_COLOR_BLUE << "b" << ANSI_COLOR_RESET << ": " << plateau.getColors()[static_cast<int>(Color::BLUE)].getNumberOfElements() << "; " << colorsPointerChecker(plateau, Color::BLUE) << ")|";
		std::cout << "(" << ANSI_COLOR_RED << "r" << ANSI_COLOR_RESET << ": " << plateau.getColors()[static_cast<int>(Color::RED)].getNumberOfElements() << "; " << colorsPointerChecker(plateau, Color::RED) << ")|";
		std::cout << "(" << ANSI_COLOR_GREEN << "g" << ANSI_COLOR_RESET << ": " << plateau.getColors()[static_cast<int>(Color::GREEN)].getNumberOfElements() << "; " << colorsPointerChecker(plateau, Color::GREEN) << ")|";
		std::cout << "(" << ANSI_COLOR_YELLOW << "y" << ANSI_COLOR_RESET << ": " << plateau.getColors()[static_cast<int>(Color::YELLOW)].getNumberOfElements() << "; " << colorsPointerChecker(plateau, Color::YELLOW) << ") || ";

		std::cout << "#: " << plateau.getSize() << " | ";
	}


	std::cout << "Next : ";
	printPiece(*plateau.getNextPieceToInsert());

	std::cout << "|| ";

	if (plateau.getNodes())
	{
		Node* temp = plateau.getNodes();

		do
		{
			temp = temp->getNextNode();
			printPiece(*(temp->getPiece()));

		} while (temp != plateau.getNodes());
	}

}

void printPiece(Piece piece)
{
	std::string form;
	std::string color;

	switch (piece.getForm())
	{
	case Form::CIRCLE:
		form = "C";
		break;
	case Form::TRIANGLE:
		form = "T";
		break;
	case Form::SQUARE:
		form = "S";
		break;
	case Form::RHOMBUS:
		form = "R";
		break;

	default:
		form = '#';
		break;
	}

	switch (piece.getColor())
	{
	case Color::RED:
		color = ANSI_COLOR_RED;
		break;
	case Color::GREEN:
		color = ANSI_COLOR_GREEN;
		break;
	case Color::YELLOW:
		color = ANSI_COLOR_YELLOW;
		break;
	case Color::BLUE:
		color = ANSI_COLOR_BLUE;
		break;

	default:
		color = ANSI_COLOR_MAGENTA;
		break;
	}

	std::cout << color << form << ANSI_COLOR_RESET << " ";
}

int waitForKeyHit() {
	char c,d,e;

	do {
		std::cin >> c;
		std::cin >> d;
		std::cin >> e;
	} while (c != 27 || d != 91);

	return e;
}

std::string formsPointerChecker(Plateau& plateau, Form form)
{
	std::string pointerStatus;

	if (plateau.getForms()[form].getFirstElement() == nullptr) {
		pointerStatus = " N";
	}
	else {
		try {
			plateau.getForms()[form].getFirstElement()->getNextForm()->getPiece()->getForm() == form;

			pointerStatus = "!N";
		}
		catch (...) {
			pointerStatus = " N";
		}
	}

	return pointerStatus;
}

std::string colorsPointerChecker(Plateau& plateau, Color color)
{
	std::string pointerStatus;

	if (plateau.getColors()[color].getFirstElement() == nullptr) {
		pointerStatus = " N";
	}
	else {
		try {
			plateau.getColors()[color].getFirstElement()->getNextColor()->getPiece()->getColor() == color;

			pointerStatus = "!N";
		}
		catch (...) {
			pointerStatus = " N";
		}
	}

	return pointerStatus;
}

void setupLinuxTerminalSettings(termios& t){
	// Black magic to prevent Linux from buffering keystrokes.
    if (tcgetattr(STDIN_FILENO, &t) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    t.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echoing
    t.c_cc[VMIN] = 1;                // Set minimum number of characters for non-canonical read
    t.c_cc[VTIME] = 0;               // Set timeout for non-canonical read

    if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}

void restoreLinuxTerminalSettings(termios& t){
    t.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}