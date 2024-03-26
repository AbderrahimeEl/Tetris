#include "../include/FormInfo.hpp"

FormInfo::FormInfo() 
: m_numberOfElements(0), m_firstElement(nullptr)
{
}

FormInfo::FormInfo(int numberOfElements, Node *firstElement)
    : m_numberOfElements(numberOfElements), m_firstElement(firstElement)
{
}

FormInfo::~FormInfo()
{
    delete m_firstElement;
}

int FormInfo::getNumberOfElements() const
{
    return m_numberOfElements;
}

Node *FormInfo::getFirstElement() const
{
    return m_firstElement;
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
