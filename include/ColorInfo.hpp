#ifndef COLOR_INFO_HPP
#define COLOR_INFO_HPP

#include "Piece.hpp"
#include "Node.hpp"

class ColorInfo
{
private:
    int m_numberOfElements;
    Node *m_firstElement;

public:
    ColorInfo();
    ColorInfo(int numberOfElements, Node *firstElement);
    ~ColorInfo();
    Node *getFirstElement() const;
    int getNumberOfElements() const;
    void setNumberOfElements(int);
    void setFirstElement(Node *);
    void incrementNumberOfElements();
    void decrementNumberOfElements();
};

#endif