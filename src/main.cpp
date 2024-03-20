#include <iostream>

#include "../include/Plateau.hpp"

void printPiece(Piece piece);

int main()
{
	Plateau plateau(15);

	while (true)
	{
		std::cout << "| C : " << plateau.getForms()[static_cast<int>(Form::CIRCLE)].getNumberOfElements() << "| ";
		std::cout << "S : " << plateau.getForms()[static_cast<int>(Form::SQUARE)].getNumberOfElements() << "| ";
		std::cout << "T : " << plateau.getForms()[static_cast<int>(Form::TRIANGLE)].getNumberOfElements() << "| ";
		std::cout << "R : " << plateau.getForms()[static_cast<int>(Form::RHOMBUS)].getNumberOfElements() << "|| ";

		std::cout << "b : " << plateau.getColors()[static_cast<int>(Color::BLUE)].getNumberOfElements() << "| ";
		std::cout << "r : " << plateau.getColors()[static_cast<int>(Color::RED)].getNumberOfElements() << "| ";
		std::cout << "g : " << plateau.getColors()[static_cast<int>(Color::GREEN)].getNumberOfElements() << "| ";
		std::cout << "y : " << plateau.getColors()[static_cast<int>(Color::YELLOW)].getNumberOfElements() << "| ";

		std::cout << "# : " << plateau.getSize() << " | next : ";
		printPiece(*plateau.getNextPieceToInsert());

		std::cout << " | ";

		if (plateau.getNodes())
		{
			Node* temp = plateau.getNodes();

			do
			{
				temp = temp->getNextNode();
				printPiece(*(temp->getPiece()));

			} while (temp != plateau.getNodes());
		}
		else
		{
			std::cout << "#";
		}

		char choice;
		std::cin >> choice;

		if (choice == 'j')
		{
			plateau.insertLeft();
			plateau.checkSideUplet(Side::LEFT) ? std::cout << "L.U" : std::cout << "!L.U";

		}
		else if (choice == 'k')
		{
			plateau.insertRight();
			bool isRightSideUplet = plateau.checkSideUplet(Side::RIGHT);
			
			if (isRightSideUplet)
			{
				plateau.deleteSideUplet(Side::RIGHT);
			}
			
			isRightSideUplet ? std::cout << "R.U" : std::cout << "!R.U";
		}
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
		color = "r";
		break;
	case Color::GREEN:
		color = "g";
		break;
	case Color::YELLOW:
		color = "y";
		break;
	case Color::BLUE:
		color = "b";
		break;

	default:
		color = "-";
		break;
	}

	std::cout << "(" << form << "/" << color << ")";
}