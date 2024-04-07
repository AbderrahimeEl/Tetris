#include <iostream>

using namespace std;

#ifdef _linux_
#include <termios.h>
#define STDIN_FILENO 0
#elif defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <conio.h>
#endif

#include "../include/Plateau.hpp"

// Keyboard key numbers
#ifdef _linux_
#define LEFT_ARROW_KEY 68
#define RIGHT_ARROW_KEY 67
#elif defined(_WIN32) || defined(_WIN64)
#define LEFT_ARROW_KEY 75
#define RIGHT_ARROW_KEY 77
#endif

#define LOWER_B_KEY 98
#define LOWER_G_KEY 103
#define LOWER_R_KEY 114
#define LOWER_Y_KEY 121
#define LOWER_C_KEY 99
#define LOWER_S_KEY 115
#define LOWER_T_KEY 116
#define LOWER_D_KEY 100

// Colors
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"

// Function declarations
void printPlateau(Plateau &plateau, bool printDetails);
void printColorList(Plateau, Color);
void printPiece(Piece piece);
int waitForKeyHit();
string formsPointerChecker(Plateau &plateau, Form form);
string colorsPointerChecker(Plateau &plateau, Color color);

#ifdef _linux_
void setupLinuxTerminalSettings(termios &t);
void restoreLinuxTerminalSettings(termios &t);
#endif

int main()
{
#ifdef _linux_
	struct termios t;
	setupLinuxTerminalSettings(t);
#endif

	Plateau plateau(15);
	bool displayDiagnosticInfo = true;

	cout << "Press left and right arrow keys to insert the next piece" << endl;
	cout << "Press b, g, r, y to shift by color" << endl;
	cout << "Press c, s, t, d to shift by form" << endl
		 << endl;

	Side side;

	while (true)
	{
		printPlateau(plateau, displayDiagnosticInfo);

		int key = waitForKeyHit();
		cout << endl;

		bool isRightSideUplet = false;
		bool isLeftSideUplet = false;

		switch (key)
		{
		case LEFT_ARROW_KEY:
			side = Side::LEFT;
			plateau.insertNode(side);
			break;

		case RIGHT_ARROW_KEY:
			side = Side::RIGHT;
			plateau.insertNode(side);
			break;

		case LOWER_B_KEY:
			plateau.shiftByColor(Color::BLUE);
			break;

		case LOWER_G_KEY:
			plateau.shiftByColor(Color::GREEN);
			break;

		case LOWER_R_KEY:
			plateau.shiftByColor(Color::RED);
			break;

		case LOWER_Y_KEY:
			plateau.shiftByColor(Color::YELLOW);
			break;

		case LOWER_C_KEY:
			plateau.shiftByForm(Form::CIRCLE);
			break;

		case LOWER_S_KEY:
			plateau.shiftByForm(Form::SQUARE);
			break;

		case LOWER_T_KEY:
			plateau.shiftByForm(Form::TRIANGLE);
			break;

		case LOWER_D_KEY:
			plateau.shiftByForm(Form::DIAMOND);
			break;

		default:
			break;
		}
	}

#ifdef _linux_
	restoreLinuxTerminalSettings(t);
#endif
}

void printPlateau(Plateau &plateau, bool printDetails)
{
	if (printDetails)
	{
		cout << "(C: " << plateau.getForms()[Form::CIRCLE].getNumberOfElements() << "; " << formsPointerChecker(plateau, Form::CIRCLE) << ")|";
		cout << "(S: " << plateau.getForms()[Form::SQUARE].getNumberOfElements() << "; " << formsPointerChecker(plateau, Form::SQUARE) << ")|";
		cout << "(T: " << plateau.getForms()[Form::TRIANGLE].getNumberOfElements() << "; " << formsPointerChecker(plateau, Form::TRIANGLE) << ")|";
		cout << "(D: " << plateau.getForms()[Form::DIAMOND].getNumberOfElements() << "; " << formsPointerChecker(plateau, Form::DIAMOND) << ") || ";

		cout << "(" << ANSI_COLOR_BLUE << "b" << ANSI_COLOR_RESET << ": " << plateau.getColors()[Color::BLUE].getNumberOfElements() << "; " << colorsPointerChecker(plateau, Color::BLUE) << ")|";
		cout << "(" << ANSI_COLOR_RED << "r" << ANSI_COLOR_RESET << ": " << plateau.getColors()[Color::RED].getNumberOfElements() << "; " << colorsPointerChecker(plateau, Color::RED) << ")|";
		cout << "(" << ANSI_COLOR_GREEN << "g" << ANSI_COLOR_RESET << ": " << plateau.getColors()[Color::GREEN].getNumberOfElements() << "; " << colorsPointerChecker(plateau, Color::GREEN) << ")|";
		cout << "(" << ANSI_COLOR_YELLOW << "y" << ANSI_COLOR_RESET << ": " << plateau.getColors()[Color::YELLOW].getNumberOfElements() << "; " << colorsPointerChecker(plateau, Color::YELLOW) << ") || ";

		cout << "#: " << plateau.getSize() << " | ";
	}

	cout << "Next : ";
	printPiece(*plateau.getNextPieceToInsert());

	cout << "|| ";

	if (plateau.getNodes())
	{
		Node *temp = plateau.getNodes();

		do
		{
			temp = temp->getNextNode();
			printPiece(*(temp->getPiece()));

		} while (temp != plateau.getNodes());
	}
}

void printPiece(Piece piece)
{
	string form;
	string color;

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
	case Form::DIAMOND:
		form = "D";
		break;

	default:
		form = "#";
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

	cout << color << form << ANSI_COLOR_RESET << " ";
}

string formsPointerChecker(Plateau &plateau, Form form)
{
	string pointerStatus;

	if (plateau.getForms()[form].getFirstElement() == nullptr)
	{
		pointerStatus = " N";
	}
	else
	{
		try
		{
			plateau.getForms()[form].getFirstElement()->getNextForm()->getPiece()->getForm() == form;

			pointerStatus = "!N";
		}
		catch (...)
		{
			pointerStatus = " N";
		}
	}

	return pointerStatus;
}

string colorsPointerChecker(Plateau &plateau, Color color)
{
	string pointerStatus;

	if (plateau.getColors()[color].getFirstElement() == nullptr)
	{
		pointerStatus = " N";
	}
	else
	{
		try
		{
			plateau.getColors()[color].getFirstElement()->getNextColor()->getPiece()->getColor() == color;

			pointerStatus = "!N";
		}
		catch (...)
		{
			pointerStatus = " N";
		}
	}

	return pointerStatus;
}

#ifdef _linux_
int waitForKeyHit()
{
	char c, d, e;

	do
	{
		cin >> c;
		cin >> d;
		cin >> e;
	} while (c != 27 || d != 91);

	return e;
}

#elif defined(_WIN32) || defined(_WIN64)

int waitForKeyHit()
{
	int pressed;
	while (!_kbhit())
		;
	pressed = _getch();

	if (pressed == 224)
	{
		pressed = _getch();
	}

	return pressed;
}
#endif

#ifdef _linux_
void setupLinuxTerminalSettings(termios &t)
{
	// Black magic to prevent Linux from buffering keystrokes.
	if (tcgetattr(STDIN_FILENO, &t) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}

	t.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echoing
	t.c_cc[VMIN] = 1;			   // Set minimum number of characters for non-canonical read
	t.c_cc[VTIME] = 0;			   // Set timeout for non-canonical read

	if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

void restoreLinuxTerminalSettings(termios &t)
{
	t.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

#endif