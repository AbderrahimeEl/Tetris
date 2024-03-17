#include "../include/Piece.hpp"

Piece::Piece()
{
}

Piece::Piece(Color color, Form form)
    : m_color(color), m_form(form)
{
}

Piece::~Piece()
{
}

Color Piece::getColor() const
{
    return this->m_color;
}

Form Piece::getForm() const
{
    return this->m_form;
}

void Piece::setColor(Color color)
{
    this->m_color = color;
}

void Piece::setForm(Form form)
{
    this->m_form = form;
}

