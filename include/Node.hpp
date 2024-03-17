#ifndef NODE_HPP
#define NODE_HPP

#include "Piece.hpp"

class Node
{
private:
    Piece *m_piece;
    Node *m_nextNode;
    Node *m_nextColor;
    Node *m_previousColor;
    Node *m_nextForm;
    Node *m_previousForm;

public:
    Node();
    Node(Node *nextNode, Node *nextColor, Node *previousColor, Node *nextForm, Node *previousForm);
    ~Node();
    Piece *getPiece() const;
    Node *getNextNode() const;
    Node *getNextColor() const;
    Node *getNextForm() const;
    Node *getPreviousColor() const;
    Node *getPreviousForm() const;
    void setPiece(Piece *piece);
    void setNextNode(Node *node);
    void setNextColor(Node *node);
    void setNextForm(Node *node);
    void setPreviousColor(Node *node);
    void setPreviousForm(Node *node);
};

#endif