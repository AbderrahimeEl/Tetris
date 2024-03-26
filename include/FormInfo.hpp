#ifndef FORM_INFO_HPP
#define FORM_INFO_HPP

#include "Piece.hpp"
#include "Node.hpp"

class FormInfo
{
private:
    int m_numberOfElements;
    Node *m_firstElement;

public:
    FormInfo();
    FormInfo(int numberOfElements, Node *firstElement);
    ~FormInfo();
    int getNumberOfElements() const;
    Node *getFirstElement() const;
    void setNumberOfElements(int numberOfElements);
    void setFirstElement(Node * firstElement);
    void incrementNumberOfElements();
    void decrementNumberOfElements();
};

#endif