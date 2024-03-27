#ifndef PLATEAU_HPP
#define PLATEAU_HPP

#include "Piece.hpp"
#include "Node.hpp"
#include "ColorInfo.hpp"
#include "FormInfo.hpp"

enum Side { LEFT, RIGHT };

class Plateau
{
private:
	const int MAX_SIZE;
	const int m_upletSize = 2;
	const int m_minPiecesForShift = 2;
	int m_score;
	int m_size;
	Node* m_tail = nullptr;
	Piece* m_nextPieceToInsert;
	ColorInfo* m_colorInfo;
	FormInfo* m_formInfo;

public:
	Plateau(int max_size);
	Plateau(int max_size, int score, int size, Node* tail, Piece* nextPieceToInsert, ColorInfo* colorInfo, FormInfo* formInfo);
	~Plateau();
	Node* getNodes() const;
	ColorInfo* getColors() const;
	FormInfo* getForms() const;
	Piece* getNextPieceToInsert() const;
	int getMaxSize() const;
	int getScore() const;
	int getSize() const;

	void setNodes(Node*);
	void setColors(ColorInfo*);
	void setForms(FormInfo*);
	void setNextPieceToInsert(Piece*);
	void setScore(int);
	void setSize(int);
	void insertNodeToSide(Side side);
	bool canPerformShift(Color color);
	void shiftByColor(Color);
	void shiftByForm(Form);
	bool checkForUplet();
	void deleteUplet();
	void deleteSideUplet(Side side);
	void increaseScoreBy(int value);
	bool checkSideUplet(Side side);

private:
	Piece* generateNextPiece();
	void updateDeletedForms(Node* temp, Node* current, Node* rightMostDeleteNode = nullptr);
	void updateDeletedColors(Node* temp, Node* current, Node* rightMostDeleteNode = nullptr);
	bool isColorUplet(Side side);
	void clearNodesList();
	void setDeletedNodesBounds(Node** leftBound, Node** rightBound, Side side);
	void updateColorUpletForms(Node*& leftMostDeleteNode, Node*& rightMostDeleteNode);
	void updateFormUpletColors(Node*& leftMostDeleteNode, Node*& rightMostDeleteNode);
	void updateColorUpletColors(Side side, Node*& leftMostDeleteNode, Node*& rightMostDeleteNode);
	void updateFormUpletForms(Side side, Node*& leftMostDeleteNode, Node*& rightMostDeleteNode);
};

#endif
