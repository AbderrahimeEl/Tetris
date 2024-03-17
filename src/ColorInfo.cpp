#include "../include/ColorInfo.hpp"

ColorInfo::ColorInfo() 
    : m_numberOfElements(0), m_firstElement(nullptr)
{
}

ColorInfo::ColorInfo(Color color, int numberOfElements, Node *firstElement) 
    : m_color(color), m_numberOfElements(numberOfElements), m_firstElement(firstElement)
{
}

ColorInfo::~ColorInfo()
{
}

Color ColorInfo::getColor() const
{
    return m_color;
}

Node *ColorInfo::getFirstElement() const
{
    return m_firstElement;
}

int ColorInfo::getNumberOfElements() const
{
    return m_numberOfElements;
}

void ColorInfo::setColor(Color color)
{
    m_color = color;
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
