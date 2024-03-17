#ifndef FORM_INFO_HPP
#define FORM_INFO_HPP

#include "Piece.hpp"
#include "Node.hpp"

class FormInfo
{
private:
    Form m_form;
    int m_numberOfElements;
    Node *m_firstElement;

public:
    FormInfo();
    FormInfo(Form form, int numberOfElements, Node *firstElement);
    ~FormInfo();
    Form getForm() const;
    int getNumberOfElements() const;
    Node *getFirstElement() const;
    void setForm(Form form);
    void setNumberOfElements(int numberOfElements);
    void setFirstElement(Node * firstElement);
    void incrementNumberOfElements();
    void decrementNumberOfElements();
};

#endif