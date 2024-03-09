#include "Plateau.hpp"

Plateau::Plateau(int max_size)
    : MAX_SIZE(max_size), m_score(0), m_numberOfPieces(0)
{
    m_tail = new Node();
    m_colorInfo = new ColorInfo[4];
    m_formInfo = new FormInfo[4];
    m_nextPieceToInsert = generateNextPiece();
}

Plateau::Plateau(int max_size, int score, int numberOfPieces, Node *tail, Piece *nextPieceToInsert, ColorInfo *colorInfo, FormInfo *formInfo)
    : MAX_SIZE(max_size), m_score(score), m_tail(tail), m_numberOfPieces(numberOfPieces), m_colorInfo(colorInfo), m_formInfo(formInfo)
{
}

Plateau::~Plateau()
{
    delete m_tail;
    delete[] m_colorInfo;
    delete[] m_formInfo;
}

Node *Plateau::getNodes() const
{
    return nullptr;
}

ColorInfo *Plateau::getColors() const
{
    return nullptr;
}

FormInfo *Plateau::getForms() const
{
    return nullptr;
}

int Plateau::getScore() const
{
    return 0;
}

Piece *Plateau::getNextPieceToInsert() const
{
    return nullptr;
}

int Plateau::getNumberOfPieces() const
{
    return 0;
}

void Plateau::setNodes(Node *)
{
}

void Plateau::setColors(ColorInfo *)
{
}

void Plateau::setForms(FormInfo *)
{
}

void Plateau::insertLeft()
{
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

int Plateau::setScore(int)
{
    return 0;
}

void Plateau::increaseScoreBy(int)
{
}

void Plateau::setNextPieceToInsert(Piece *)
{
}

void Plateau::setNumberOfPieces(int)
{
}

Piece *Plateau::generateNextPiece()
{
}
