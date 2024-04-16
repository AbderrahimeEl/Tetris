#ifndef PIECE_CPP
#define PIECE_CPP

enum _Color
{
    _RED,
    _GREEN,
    _BLUE,
    _YELLOW
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
    _Color m_color;
    Form m_form;

public:
    Piece();
    Piece(_Color color, Form form);
    ~Piece();
    _Color getColor() const;
    Form getForm() const;
    void setColor(_Color color);
    void setForm(Form form);
};

#endif
