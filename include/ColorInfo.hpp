#ifndef COLOR_INFO_HPP
#define COLOR_INFO_HPP

#include "Piece.hpp"
#include "Node.hpp"

class ColorInfo
{
private:
    Color m_color;
    int m_numberOfElements;
    Node *m_firstElement;

public:
    ColorInfo();
    ColorInfo(Color color, int numberOfElements, Node *firstElement);
    ~ColorInfo();
    Color getColor() const;
    Node *getFirstElement() const;
    int getNumberOfElements() const;
    void setColor(Color color);
    void setNumberOfElements(int);
    void setFirstElement(Node *);
    void incrementNumberOfElements();
    void decrementNumberOfElements();
};

#endif