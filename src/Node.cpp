#include "../include/Node.hpp"

Node::Node()
{
}
Node::Node(Node *nextNode, Node *nextColor, Node *previousColor, Node *nextForm, Node *previousForm)
    : m_nextNode(nextNode), m_nextColor(nextColor), m_previousColor(previousColor), m_nextForm(nextForm), m_previousForm(previousForm)
{
}

Node::~Node()
{
}

Piece *Node::getPiece() const
{
    return m_piece;
}

Node *Node::getNextNode() const
{
    return m_nextNode;
}

Node *Node::getNextColor() const
{
    return m_nextColor;
}

Node *Node::getNextForm() const
{
    return m_nextForm;
}

Node *Node::getPreviousColor() const
{
    return m_previousColor;
}

Node *Node::getPreviousForm() const
{
    return m_previousForm;
}

void Node::setPiece(Piece *piece)
{
    m_piece = piece;
}

void Node::setNextNode(Node *node)
{
    m_nextNode = node;
}

void Node::setNextColor(Node *node)
{
    m_nextColor = node;
}

void Node::setNextForm(Node *node)
{
    m_nextForm = node;
}

void Node::setPreviousColor(Node *node)
{
    m_previousColor = node;
}

void Node::setPreviousForm(Node *node)
{
    m_previousForm = node;
}
