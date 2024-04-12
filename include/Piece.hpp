#ifndef PIECE_CPP
#define PIECE_CPP

enum Color
{
    RED,
    GREEN,
    BLUE,
    YELLOW
};

enum Form
{
    SQUARE,
    CIRCLE,
    TRIANGLE,
    DIAMOND
};

class Piece
{
private:
    Color m_color;
    Form m_form;

public:
    Piece();
    Piece(Color color, Form form);
    ~Piece();
    Color getColor() const;
    Form getForm() const;
    void setColor(Color color);
    void setForm(Form form);
};

#endif
