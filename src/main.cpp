#include <iostream>

#include "../include/Plateau.hpp"

void printPiece(Piece piece);

int main()
{
    Plateau plateau(15);

    while (true)
    {
        std::cout << "C : " << plateau.getForms()[static_cast<int>(Form::CIRCLE)].getNumberOfElements() << "| ";
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
            Node *temp = plateau.getNodes();

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

        std::getchar();
        plateau.insertLeft();
    }
}

void printPiece(Piece piece)
{
    std::string form;
    std::string color;

    // switch (piece.getForm())
    // {
    // case Form::CIRCLE:
    //     form = CIRCLE_SYMBOL;
    //     break;
    // case Form::TRIANGLE:
    //     form = TRIANGLE_SYMBOL;
    //     break;
    // case Form::SQUARE:
    //     form = SQUARE_SYMBOL;
    //     break;
    // case Form::RHOMBUS:
    //     form = RHOMBUS_SYMBOL;
    //     break;

    // default:
    //     form = '#';
    //     break;
    // }
    
    // switch (piece.getColor())
    // {
    // case Color::RED:
    //     color = ANSI_COLOR_RED;
    //     break;
    // case Color::GREEN:
    //     color = ANSI_COLOR_GREEN;
    //     break;
    // case Color::YELLOW:
    //     color = ANSI_COLOR_YELLOW;
    //     break;
    // case Color::BLUE:
    //     color = ANSI_COLOR_BLUE;
    //     break;

    // default:
    //     color = ANSI_COLOR_RESET;
    //     break;
    // }

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

    // std::cout << color << form << ANSI_COLOR_RESET;
    std::cout << "("<< form << "/" << color << ")";
}