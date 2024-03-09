#include "Piece.hpp"
#include "Node.hpp"
#include "ColorInfo.hpp"
#include "FormInfo.hpp"

#ifndef PLATEAU_HPP
#define PLATEAU_HPP

class Plateau
{
private:
    const int MAX_SIZE;
    int m_score;
    int m_numberOfPieces;
    Node* m_tail;
    Piece *m_nextPieceToInsert;
    ColorInfo *m_colorInfo;
    FormInfo *m_formInfo;

public:
    Plateau(int max_size);
    Plateau(int max_size, int score, int numberOfPieces, Node* tail, Piece *nextPieceToInsert, ColorInfo *colorInfo, FormInfo *formInfo);
    ~Plateau();
    Node *getNodes() const;
    ColorInfo *getColors() const;
    FormInfo *getForms() const;
    Piece *getNextPieceToInsert() const;
    int getMaxSize() const;
    int getScore() const;
    int getNumberOfPieces() const;

    void setNodes(Node *);
    void setColors(ColorInfo *);
    void setForms(FormInfo *);
    void setNextPieceToInsert(Piece *);
    int setScore(int);
    void setNumberOfPieces(int);
    void insertRight();
    void insertLeft();
    bool canPerformShift();
    void shiftByColor(Color);
    void shiftByForm(Form);
    bool checkForUplet();
    void deleteUplet();
    void increaseScoreBy(int);

private:
    Piece *generateNextPiece();
};

#endif
