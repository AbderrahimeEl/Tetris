#include "../include/Node.hpp"
#include "Node.hpp"

Node::Node()
{
}
Node::Node(Node *m_nextNode, Node *m_nextColor, Node *m_previousColor, Node *m_nextForm, Node *m_previousForm)
{
}

Node::~Node()
{
}

Piece *Node::getPiece() const
{
    return nullptr;
}

Node *Node::getNextNode() const
{
    return nullptr;
}

Node *Node::getNextColor() const
{
    return nullptr;
}

Node *Node::getNextForm() const
{
    return nullptr;
}

Node *Node::getPreviousColor() const
{
    return nullptr;
}

Node *Node::getPreviousForm() const
{
    return nullptr;
}

void Node::setPiece(Piece *piece)
{
}

void Node::setNextNode(Node *node)
{
}

void Node::setNextColor(Node *node)
{
}

void Node::setNextForm(Node *node)
{
}

void Node::setPreviousColor(Node *node)
{
}

void Node::setPreviousForm(Node *node)
{
}

