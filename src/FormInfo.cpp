#include "../include/FormInfo.hpp"

FormInfo::FormInfo() 
: m_numberOfElements(0), m_firstElement(nullptr)
{
}

FormInfo::FormInfo(Form form, int numberOfElements, Node *firstElement)
    : m_form(form), m_numberOfElements(numberOfElements), m_firstElement(firstElement)
{
}

FormInfo::~FormInfo()
{
}

Form FormInfo::getForm() const
{
    return m_form;
}

int FormInfo::getNumberOfElements() const
{
    return m_numberOfElements;
}

Node *FormInfo::getFirstElement() const
{
    return m_firstElement;
}

void FormInfo::setForm(Form form)
{
    m_form = form;
}

void FormInfo::setNumberOfElements(int numberOfElements)
{
    m_numberOfElements = numberOfElements;
}

void FormInfo::setFirstElement(Node *firstElement)
{
    m_firstElement = firstElement;
}

void FormInfo::incrementNumberOfElements()
{
    m_numberOfElements++;
}

void FormInfo::decrementNumberOfElements()
{
    if (m_numberOfElements > 0)
    {
        m_numberOfElements--;
    }
}
