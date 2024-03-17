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
            m_tail = insertedNode;
            insertedNode->setNextNode(insertedNode);

            // (2) color
            insertedNode->setNextColor(insertedNode);
            insertedNode->setPreviousColor(insertedNode);

            int index = static_cast<int>(insertedNode->getPiece()->getColor());
            m_colorInfo[index].setFirstElement(insertedNode);
            m_colorInfo[index].incrementNumberOfElements();

            // (3) form
            insertedNode->setNextForm(insertedNode);
            insertedNode->setPreviousForm(insertedNode);

            index = static_cast<int>(insertedNode->getPiece()->getForm());
            m_formInfo[index].setFirstElement(insertedNode);
            m_formInfo[index].incrementNumberOfElements();
        }
        else
        {
            // (1) nodes list
            insertedNode->setNextNode(m_tail->getNextNode());
            m_tail->setNextNode(insertedNode);

            // (2) color
            int index = static_cast<int>(insertedNode->getPiece()->getColor());

            if (m_colorInfo[index].getNumberOfElements() == 0)
            {
                m_colorInfo[index].setFirstElement(insertedNode);

                insertedNode->setNextColor(insertedNode);
                insertedNode->setPreviousColor(insertedNode);
            }
            else
            {
                insertedNode->setNextColor(m_colorInfo[index].getFirstElement()->getNextColor());
                m_colorInfo[index].getFirstElement()->getNextColor()->setPreviousColor(insertedNode);
                m_colorInfo[index].getFirstElement()->setNextColor(insertedNode);
                insertedNode->setPreviousColor(m_colorInfo[index].getFirstElement());
            }

            m_colorInfo[index].incrementNumberOfElements();

            // (3) form
            index = static_cast<int>(insertedNode->getPiece()->getForm());

            if (m_formInfo[index].getNumberOfElements() == 0)
            {
                m_formInfo[index].setFirstElement(insertedNode);

                insertedNode->setNextForm(insertedNode);
                insertedNode->setPreviousForm(insertedNode);
            }
            else
            {
                insertedNode->setNextForm(m_formInfo[index].getFirstElement()->getNextForm());
                m_formInfo[index].getFirstElement()->getNextForm()->setPreviousForm(insertedNode);
                m_formInfo[index].getFirstElement()->setNextForm(insertedNode);
                insertedNode->setPreviousForm(m_formInfo[index].getFirstElement());
            }

            m_formInfo[index].incrementNumberOfElements();
        }

        m_size++;
        m_nextPieceToInsert = generateNextPiece();
    }
}

void Plateau::insertRight()
{
    if (m_size < MAX_SIZE)
    {
        Node *insertedNode = new Node();
        insertedNode->setPiece(m_nextPieceToInsert);

        if (m_size == 0)
        {
            // (1) nodes list
            m_tail = insertedNode;
            insertedNode->setNextNode(insertedNode);

            // (2) color
            insertedNode->setNextColor(insertedNode);
            insertedNode->setPreviousColor(insertedNode);

            int index = static_cast<int>(insertedNode->getPiece()->getColor());
            m_colorInfo[index].setFirstElement(insertedNode);

            m_colorInfo[index].incrementNumberOfElements();

            // // (3) form
            insertedNode->setNextForm(insertedNode);
            insertedNode->setPreviousForm(insertedNode);

            index = static_cast<int>(insertedNode->getPiece()->getForm());
            m_formInfo[index].setFirstElement(insertedNode);

            m_formInfo[index].incrementNumberOfElements();
        }
        else
        {
            // (1) nodes list
            insertedNode->setNextNode(m_tail->getNextNode());
            m_tail->setNextNode(insertedNode);
            m_tail = insertedNode;

            // (2) color
            int index = static_cast<int>(insertedNode->getPiece()->getColor());

            if (m_colorInfo[index].getNumberOfElements() == 0)
            {
                m_colorInfo[index].setFirstElement(insertedNode);

                insertedNode->setNextColor(insertedNode);
                insertedNode->setPreviousColor(insertedNode);
            }
            else
            {
                insertedNode->setNextColor(m_colorInfo[index].getFirstElement()->getNextColor());
                m_colorInfo[index].getFirstElement()->getNextColor()->setPreviousColor(insertedNode);
                m_colorInfo[index].getFirstElement()->setNextColor(insertedNode);
                insertedNode->setPreviousColor(m_colorInfo[index].getFirstElement());

                m_colorInfo[index].setFirstElement(insertedNode);
            }

            m_colorInfo[index].incrementNumberOfElements();

            // (3) form
            index = static_cast<int>(insertedNode->getPiece()->getForm());

            if (m_formInfo[index].getNumberOfElements() == 0)
            {
                m_formInfo[index].setFirstElement(insertedNode);

                insertedNode->setNextForm(insertedNode);
                insertedNode->setPreviousForm(insertedNode);
            }
            else
            {
                insertedNode->setNextForm(m_formInfo[index].getFirstElement()->getNextForm());
                m_formInfo[index].getFirstElement()->getNextForm()->setPreviousForm(insertedNode);
                m_formInfo[index].getFirstElement()->setNextForm(insertedNode);
                insertedNode->setPreviousForm(m_formInfo[index].getFirstElement());

                m_formInfo[index].setFirstElement(insertedNode);
            }

            m_formInfo[index].incrementNumberOfElements();
        }

        m_size++;
        m_nextPieceToInsert = generateNextPiece();
    }
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
