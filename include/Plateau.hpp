#ifndef PLATEAU_HPP
#define PLATEAU_HPP

#include "Piece.hpp"
#include "Node.hpp"
#include "ColorInfo.hpp"
#include "FormInfo.hpp"

enum Side
{
	LEFT,
	RIGHT
};

enum Shift
{
	COLOR,
	FORM
};

class Plateau
{
private:
	const int MAX_SIZE;
	const int m_upletSize = 3;
	int m_score;
	int m_size;
	Node *m_tail = nullptr;
	Piece *m_nextPieceToInsert;
	ColorInfo *m_colorInfo;
	FormInfo *m_formInfo;

public:
	Plateau(int max_size);
	Plateau(int max_size, int score, int size, Node *tail, Piece *nextPieceToInsert, ColorInfo *colorInfo, FormInfo *formInfo);
	~Plateau();
	Node *getNodes() const;
	ColorInfo *getColors() const;
	FormInfo *getForms() const;
	Piece *getNextPieceToInsert() const;
	int getMaxSize() const;
	int getScore() const;
	int getSize() const;

	void setNodes(Node *);
	void setColors(ColorInfo *);
	void setForms(FormInfo *);
	void setNextPieceToInsert(Piece *);
	void setScore(int);
	void setSize(int);
	void insertNode(Side side);
	void increaseScoreBy(int value);
	bool canPerformShift();
	void shiftByColor(Color);
	void shiftByForm(Form);
	void swapPiece(Node *, Node *, Shift);
	void deleteUplet();
	bool isColorUplet(Node *, Node **);
	bool isFormUplet(Node *, Node **);

private:
	Piece *generateNextPiece();
	void clearNodesList();
	void clearUplet(Node *);
	void updateUpletColor(Node *, Node *);
	void updateUpletForm(Node *, Node *);
	void updateUpletColorForm(Node *, Node *);
};

#endif