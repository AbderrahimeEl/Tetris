#include "../include/ColorInfo.hpp"

ColorInfo::ColorInfo() 
    : m_numberOfElements(0), m_firstElement(nullptr)
{
}

ColorInfo::ColorInfo(int numberOfElements, Node *firstElement) 
    : m_numberOfElements(numberOfElements), m_firstElement(firstElement)
{
}

ColorInfo::~ColorInfo()
{
    delete m_firstElement;
}

Node *ColorInfo::getFirstElement() const
{
    return m_firstElement;
}

int ColorInfo::getNumberOfElements() const
{
    return m_numberOfElements;
}

void ColorInfo::setNumberOfElements(int numberOfElements)
{
    m_numberOfElements = numberOfElements;
}

void ColorInfo::setFirstElement(Node * firstElement)
{
    m_firstElement = firstElement;
}

void ColorInfo::incrementNumberOfElements()
{
    m_numberOfElements++;
}

void ColorInfo::decrementNumberOfElements()
{
    if (m_numberOfElements > 0)
    {
        m_numberOfElements--;
    }
}
