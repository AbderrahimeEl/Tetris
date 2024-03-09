#include "Piece.hpp"
#include "Node.hpp"

#ifndef FORM_INFO.HPP
#define FORM_INFO .HPP

class FormInfo
{
private:
    Form form;
    int numberOfElements;
    Node *firstElement;

public:
    FormInfo();
    FormInfo(Form form, int numberOfElements, Node *firstElement);
    ~FormInfo();
    Form getForm() const;
    int getNumberOfElements() const;
    Node *getFirstElement() const;
    void setForm(Form);
    void setNumberOfElements(int);
    void setFirstElement(Node *);
};

#endif