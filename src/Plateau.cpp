#include "../include/Plateau.hpp"
#include <stdlib.h>

Plateau::Plateau(int max_size)
    : MAX_SIZE(max_size), m_score(0), m_size(0), m_colorInfo(new ColorInfo[4]), m_formInfo(new FormInfo[4])
{
    m_nextPieceToInsert = generateNextPiece();
}

Plateau::Plateau(int max_size, int score, int size, Node *tail, Piece *nextPieceToInsert, ColorInfo *colorInfo, FormInfo *formInfo)
    : MAX_SIZE(max_size), m_score(score), m_tail(tail), m_size(size)
{
    // this->m_colorInfo = colorInfo;
    // m_formInfo =formInfo;
}

Plateau::~Plateau()
{
    delete m_tail;
    delete[] m_colorInfo;
    delete[] m_formInfo;
}

Node *Plateau::getNodes() const
{
    return m_tail;
}

ColorInfo *Plateau::getColors() const
{
    return m_colorInfo;
}

FormInfo *Plateau::getForms() const
{
    return m_formInfo;
}

int Plateau::getScore() const
{
    return m_score;
}

Piece *Plateau::getNextPieceToInsert() const
{
    return m_nextPieceToInsert;
}

int Plateau::getSize() const
{
    return m_size;
}

void Plateau::setNodes(Node *nodes)
{
    m_tail = nodes;
}

void Plateau::setColors(ColorInfo *colorInfo)
{
    m_colorInfo = colorInfo;
}

void Plateau::setForms(FormInfo *formInfo)
{
    m_formInfo = formInfo;
}

void Plateau::insertLeft()
{
    if (m_size < MAX_SIZE)
    {
        Node *insertedNode = new Node();
        insertedNode->setPiece(m_nextPieceToInsert);

        if (m_size == 0)
        {
            // (1) nodes list
            // set tail = insertedNode
            m_tail = insertedNode;

            // set next for insertedNode to null
            insertedNode->setNextNode(insertedNode);

            // (2) color
            // (2.1) update the colors doubly linked List
            // set nextColor for insertedNode to insertedNode
            insertedNode->setNextColor(insertedNode);
            // set previousColor for insertedNode to insertedNode
            insertedNode->setPreviousColor(insertedNode);

            // (2.2) update the colorInfo List
            // set pointer for colorInfo to insertedNode
            int index = static_cast<int>(insertedNode->getPiece()->getColor());
            m_colorInfo[index].setFirstElement(insertedNode);
            // increase color count
            m_colorInfo[index].incrementNumberOfElements();

            // (3) form
            // (3.1) update the forms doubly linked List
            // set nextForm for insertedNode to insertedNode
            insertedNode->setNextForm(insertedNode);
            // set previousForm for insertedNode to insertedNode
            insertedNode->setPreviousForm(insertedNode);

            // (3.2) update the formInfo List
            // set pointer for formInfo to insertedNode
            index = static_cast<int>(insertedNode->getPiece()->getForm());
            m_formInfo[index].setFirstElement(insertedNode);
            // increase form count
            m_formInfo[index].incrementNumberOfElements();
        }
        else
        {
            // else
            // (1) nodes list
            // set next for insertedNode to tail.next
            insertedNode->setNextNode(m_tail->getNextNode());
            // set next for tail to insertedNode
            m_tail->setNextNode(insertedNode);

            // // (2) color
            // // if insertedNode.color.count == 0 // the first update our colorInfo List
            int index = static_cast<int>(insertedNode->getPiece()->getColor());
            // m_colorInfo[index].setFirstElement(insertedNode);

            if (m_colorInfo[index].getNumberOfElements() == 0)
            {
                // (2.1) colorInfo list
                // set this on to be tail
                m_colorInfo[index].setFirstElement(insertedNode);

                // (2.2) color list
                // set nextColor for insertedNode to insertedNode
                insertedNode->setNextColor(insertedNode);
                // set previousColor for insertedNode to insertedNode
                insertedNode->setPreviousColor(insertedNode);
            }
            else
            {
                // else // the other one is the tail
                // (2.2) color list
                // set nextColor for insertedNode to tail->nextColor
                insertedNode->setNextColor(m_tail->getNextColor());

                // set previous for tail->next to insertedNode
                m_tail->getNextColor()->setPreviousColor(insertedNode);

                // set next for tail to insertedNode
                m_tail->setNextColor(insertedNode);
                // set previous for insertedNode to tail
                insertedNode->setPreviousColor(m_tail);
            }

            // increase color count
            m_colorInfo[index].incrementNumberOfElements();

            // (3) form
            // if insertedNode.form.count == 0 // the first update our colorInfo List
            index = static_cast<int>(insertedNode->getPiece()->getForm());
            m_formInfo[index].setFirstElement(insertedNode);

            if (m_formInfo[index].getNumberOfElements() == 0)
            {
                // (2.1) FormInfo list
                // set this on to be tail
                m_formInfo[index].setFirstElement(insertedNode);

                // (2.2) form list
                // set nextForm for insertedNode to insertedNode
                insertedNode->setNextForm(insertedNode);
                // set previousForm for insertedNode to insertedNode
                insertedNode->setPreviousForm(insertedNode);
            }
            else
            {
                // else // the other one is the tail
                // (2.2) form list
                // set nextForm for insertedNode to tail->nextForm
                insertedNode->setNextForm(m_tail->getNextForm());

                // set previous for tail->next to insertedNode
                m_tail->getNextForm()->setPreviousForm(insertedNode);

                // set next for tail to insertedNode
                m_tail->setNextForm(insertedNode);
                // set previous for insertedNode to tail
                insertedNode->setPreviousForm(m_tail);
            }

            // increase form count
            m_formInfo[index].incrementNumberOfElements();
        }

        // increase size
        m_size++;

        m_nextPieceToInsert = generateNextPiece();
    }
}

void Plateau::insertRight()
{
}

bool Plateau::canPerformShift()
{
    return false;
}

void Plateau::shiftByColor(Color)
{
}

void Plateau::shiftByForm(Form)
{
}

bool Plateau::checkForUplet()
{
    return false;
}

void Plateau::deleteUplet()
{
}

void Plateau::setScore(int score)
{
    m_score = score;
}

void Plateau::increaseScoreBy(int value)
{
    m_score += value;
}

void Plateau::setNextPieceToInsert(Piece *piece)
{
    m_nextPieceToInsert = piece;
}

void Plateau::setSize(int size)
{
    m_size = size;
}

Piece *Plateau::generateNextPiece()
{
    int randomColor = rand() % 4;
    int randomForm = rand() % 4;

    return new Piece(static_cast<Color>(randomColor), static_cast<Form>(randomForm));
}
