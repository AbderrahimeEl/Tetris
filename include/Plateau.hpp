#ifndef PLATEAU_HPP
#define PLATEAU_HPP

#include "Piece.hpp"
#include "Node.hpp"
#include "ColorInfo.hpp"
#include "FormInfo.hpp"
#include <string>

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
	int m_upletSize = 3;
	const int m_minPiecesForShift = 2;
	int m_score;
	int m_size;
	int m_shiftTentatives = 6;
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
	int getScore();
	int getSize();
	int getUpletSize();
	int getShiftTentetives();

	void setNodes(Node *);
	void setColors(ColorInfo *);
	void setForms(FormInfo *);
	void setNextPieceToInsert(Piece *);
	void setScore(int);
	void setSize(int);
	void setUpletSize(int);
	void setShiftTentetives(int);

	void increaseScore(int level);
	void updateScores();

	void insertNode(Side side);
	bool canPerformShift();
	void shiftByColor(_Color);
	void shiftByForm(Form);
	void swapPiece(Node *, Node *, Shift);
	void deleteUplet();
	bool isColorUplet(Node *, Node **);
	bool isFormUplet(Node *, Node **);
	void LoadSavedPlateau(std::string);
	void savePlateauToFile(const std::string &filename);
	void LoadPlateauFromFile(const std::string &filename);

private:
	Piece *generateNextPiece();
	void clearNodesList();
	void clearUplet(Node *);
	void updateUpletColor(Node *, Node *);
	void updateUpletForm(Node *, Node *);
	void updateUpletColorForm(Node *, Node *);
};

#endif