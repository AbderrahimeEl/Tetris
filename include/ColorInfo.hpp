#include "Piece.hpp"
#include "Node.hpp"

#ifndef COLOR_INFO_HPP
#define COLOR_INFO_HPP

class ColorInfo
{
private:
    Color color;
    int numberOfElements;
    Node *firstElement;

public:
    ColorInfo();
    ColorInfo(Color color, int numberOfElements, Node *firstElement);
    ~ColorInfo();
    Color getColor() const;
    Node *getFirstElement() const;
    int getNumberOfElements() const;
    void setColor(Color);
    void setNumberOfElements(int);
    void setFirstElement(Node *);
};

#endif