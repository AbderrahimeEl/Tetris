#include "../include/Plateau.hpp"
#include <stdlib.h>

Plateau::Plateau(int max_size)
	: MAX_SIZE(max_size), m_score(0), m_size(0), m_colorInfo(new ColorInfo[4]), m_formInfo(new FormInfo[4])
{
	m_nextPieceToInsert = generateNextPiece();
}

Plateau::Plateau(int max_size, int score, int size, Node* tail, Piece* nextPieceToInsert, ColorInfo* colorInfo, FormInfo* formInfo)
	: MAX_SIZE(max_size), m_score(score), m_tail(tail), m_size(size)
{
}

Plateau::~Plateau()
{
	delete m_tail;
	delete[] m_colorInfo;
	delete[] m_formInfo;
}

Node* Plateau::getNodes() const
{
	return m_tail;
}

ColorInfo* Plateau::getColors() const
{
	return m_colorInfo;
}

FormInfo* Plateau::getForms() const
{
	return m_formInfo;
}

int Plateau::getScore() const
{
	return m_score;
}

Piece* Plateau::getNextPieceToInsert() const
{
	return m_nextPieceToInsert;
}

int Plateau::getSize() const
{
	return m_size;
}

void Plateau::setNodes(Node* nodes)
{
	m_tail = nodes;
}

void Plateau::setColors(ColorInfo* colorInfo)
{
	m_colorInfo = colorInfo;
}

void Plateau::setForms(FormInfo* formInfo)
{
	m_formInfo = formInfo;
}

void Plateau::setScore(int score)
{
	m_score = score;
}

void Plateau::increaseScoreBy(int value)
{
	m_score += value;
}

void Plateau::setNextPieceToInsert(Piece* piece)
{
	m_nextPieceToInsert = piece;
}

void Plateau::setSize(int size)
{
	m_size = size;
}

Piece* Plateau::generateNextPiece()
{
	int randomColor = rand() % 4;
	int randomForm = rand() % 4;

	return new Piece(static_cast<Color>(randomColor), static_cast<Form>(randomForm));
}

int Plateau::getMaxSize() const {
	return MAX_SIZE;
}

void Plateau::insertNodeToSide(Side side)
{
	if (m_size >= MAX_SIZE || m_size < 0)
	{
		return;
	}

	Node* insertedNode = new Node();
	insertedNode->setPiece(m_nextPieceToInsert);

	if (m_size == 0)
	{
		// (1) update nodes list
		m_tail = insertedNode;
		insertedNode->setNextNode(insertedNode);

		// (2) update colors lists
		insertedNode->setNextColor(insertedNode);
		insertedNode->setPreviousColor(insertedNode);

		int index = static_cast<int>(insertedNode->getPiece()->getColor());
		m_colorInfo[index].setFirstElement(insertedNode);
		m_colorInfo[index].incrementNumberOfElements();

		// (3) update forms lists
		insertedNode->setNextForm(insertedNode);
		insertedNode->setPreviousForm(insertedNode);

		index = static_cast<int>(insertedNode->getPiece()->getForm());
		m_formInfo[index].setFirstElement(insertedNode);
		m_formInfo[index].incrementNumberOfElements();

		m_size++;
		m_nextPieceToInsert = generateNextPiece();

		return;
	}

	// (1) update nodes list
	insertedNode->setNextNode(m_tail->getNextNode());
	m_tail->setNextNode(insertedNode);

	if (side == Side::RIGHT)
	{
		m_tail = insertedNode;
	}

	// (2) update colors lists
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

		if (side == Side::RIGHT)
		{
			m_colorInfo[index].setFirstElement(insertedNode);
		}
	}

	m_colorInfo[index].incrementNumberOfElements();

	// (3) update forms lists
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

		if (side == Side::RIGHT)
		{
			m_formInfo[index].setFirstElement(insertedNode);
		}
	}

	m_formInfo[index].incrementNumberOfElements();


	m_size++;
	m_nextPieceToInsert = generateNextPiece();
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

bool Plateau::checkSideUplet(Side side)
{
	Node* node = side == Side::RIGHT ? node = m_tail : node = m_tail->getNextNode();

	int colorIndex = static_cast<int>(node->getPiece()->getColor());
	int formIndex = static_cast<int>(node->getPiece()->getForm());

	bool hasMinimumSameColor = m_colorInfo[colorIndex].getNumberOfElements() >= m_upletSize ? true : false;
	bool hasMinimumSameForm = m_formInfo[formIndex].getNumberOfElements() >= m_upletSize ? true : false;

	// Check if we have enough pieces of the same color or shape to create an uplet
	if (!(hasMinimumSameColor || hasMinimumSameForm))
	{
		return false;
	}

	bool isColorUplet = true;
	bool isFormUplet = true;

	if (side == Side::RIGHT)
	{
		if (hasMinimumSameColor)
		{
			Node* current = m_tail;

			for (int i = 0; i < m_upletSize - 1; i++)
			{
				if (current->getPreviousColor()->getNextNode() == current)
				{
					current = current->getPreviousColor();
				}
				else
				{
					isColorUplet = false;
					break;
				}
			}
		}
		else
		{
			isColorUplet = false;
		}

		if (hasMinimumSameForm)
		{
			Node* current = m_tail;

			for (int i = 0; i < m_upletSize - 1; i++)
			{
				if (current->getPreviousForm()->getNextNode() == current)
				{
					current = current->getPreviousForm();
				}
				else
				{
					isFormUplet = false;
					break;
				}
			}
		}
		else
		{
			isFormUplet = false;
		}

		return isColorUplet || isFormUplet;
	}
	else
	{
		if (hasMinimumSameColor)
		{
			Node* current = m_tail->getNextNode();

			for (int i = 0; i < m_upletSize - 1; i++)
			{
				if (current->getNextColor() == current->getNextNode())
				{
					current = current->getNextNode();
				}
				else
				{
					isColorUplet = false;
					break;
				}
			}
		}
		else
		{
			isColorUplet = false;
		}

		if (hasMinimumSameForm)
		{
			Node* current = m_tail->getNextNode();

			for (int i = 0; i < m_upletSize - 1; i++)
			{
				if (current->getNextForm() == current->getNextNode())
				{
					current = current->getNextNode();
				}
				else
				{
					isFormUplet = false;
					break;
				}
			}
		}
		else
		{
			isFormUplet = false;
		}

		return isColorUplet || isFormUplet;
	}
}

void Plateau::deleteUplet()
{
}

void Plateau::deleteSideUplet(Side side)
{
	if (m_upletSize > m_size)
	{
		return;
	}

	if (m_upletSize == m_size)
	{
		clearNodesList();
		return;
	}

	Node* rightMostDeleteNode = nullptr;
	Node* leftMostDeleteNode = nullptr;

	setDeletedNodesBounds(&leftMostDeleteNode, &rightMostDeleteNode, side);

	// update colors/forms and formInfo/colorInfo lists
	bool isColorUplet = this->isColorUplet(side);

	if (isColorUplet)
	{
		updateColorUpletColors(side, leftMostDeleteNode, rightMostDeleteNode);
		updateColorUpletForms(leftMostDeleteNode, rightMostDeleteNode);
	}
	else
	{
		updateFormUpletForms(side, leftMostDeleteNode, rightMostDeleteNode);
		updateFormUpletColors(leftMostDeleteNode, rightMostDeleteNode);
	}

	// update nodes list and the tail
	if (side == Side::RIGHT)
	{
		Node* new_head = m_tail;
		for (int i = 0; i < m_size - m_upletSize; i++)
		{
			new_head = new_head->getNextNode();
		}

		new_head->setNextNode(m_tail->getNextNode());
		m_tail->setNextNode(nullptr);

		m_tail = new_head;
	}
	else if (side == Side::LEFT)
	{
		Node* new_head = rightMostDeleteNode->getNextNode();
		m_tail->setNextNode(new_head);
	}

	m_size -= m_upletSize;

	// free memory
	for (int i = 0; i < m_upletSize; i++)
	{
		Node* next = leftMostDeleteNode->getNextNode();
		delete leftMostDeleteNode;
		leftMostDeleteNode = next;
	}
}

void Plateau::clearNodesList()
{
	// clear nodes list
	Node* current = m_tail;
	for (int i = 0; i < m_size; i++)
	{
		Node* next = current->getNextNode();
		delete current;
		current = next;
	}

	m_tail = nullptr;
	m_size = 0;

	// reset colorInfo and formInfoList (firstElement, numberOfElements)
	for (int i = 0; i < 4; i++)
	{
		m_colorInfo[i].setFirstElement(nullptr);
		m_colorInfo[i].setNumberOfElements(0);
		m_formInfo[i].setFirstElement(nullptr);
		m_formInfo[i].setNumberOfElements(0);
	}
}

bool Plateau::isColorUplet(Side side)
{
	bool isColorUplet = true;

	if (side == Side::RIGHT)
	{
		Node* current = m_tail;

		for (int i = 0; i < m_upletSize - 1; i++)
		{
			if (current->getPreviousColor()->getNextNode() != current)
			{
				isColorUplet = false;
				break;
			}

			current = current->getPreviousColor();
		}
	}
	else if (side == Side::LEFT)
	{
		// head 
		Node* current = m_tail->getNextNode();

		for (int i = 0; i < m_upletSize - 1; i++)
		{
			if (current->getNextColor() != current->getNextNode())
			{
				isColorUplet = false;
				break;
			}

			current = current->getNextColor();
		}
	}

	return isColorUplet;
}

void Plateau::setDeletedNodesBounds(Node** leftMostDeleteNode, Node** rightMostDeleteNode, Side side)
{
	bool isColorUplet = this->isColorUplet(side);

	if (side == Side::RIGHT)
	{
		*rightMostDeleteNode = m_tail;
		*leftMostDeleteNode = m_tail;

		if (isColorUplet)
		{
			for (int i = 0; i < m_upletSize - 1; i++)
			{
				*leftMostDeleteNode = (*leftMostDeleteNode)->getPreviousColor();
			}
		}
		else
		{
			for (int i = 0; i < m_upletSize - 1; i++)
			{
				*leftMostDeleteNode = (*leftMostDeleteNode)->getPreviousForm();
			}
		}
	}
	else
	{
		*rightMostDeleteNode = m_tail->getNextNode();
		*leftMostDeleteNode = m_tail->getNextNode();

		if (isColorUplet)
		{
			for (int i = 0; i < m_upletSize - 1; i++)
			{
				*rightMostDeleteNode = (*rightMostDeleteNode)->getNextColor();
			}
		}
		else
		{
			for (int i = 0; i < m_upletSize - 1; i++)
			{
				*rightMostDeleteNode = (*rightMostDeleteNode)->getNextForm();
			}
		}
	}
}

void Plateau::updateColorUpletColors(Side side, Node*& leftMostDeleteNode, Node*& rightMostDeleteNode) {
	if (side == Side::LEFT)
	{
		if (rightMostDeleteNode == m_colorInfo[rightMostDeleteNode->getPiece()->getColor()].getFirstElement())
		{
			// cas 1 - tous les pieces de cette couleur seront supprimer dans cette uplet
			m_colorInfo[leftMostDeleteNode->getPiece()->getColor()].setNumberOfElements(0);
			m_colorInfo[leftMostDeleteNode->getPiece()->getColor()].setFirstElement(nullptr);
		}
		else
		{
			// cas 2 - il existe encore des pieces de cette couleur dans le plateau
			leftMostDeleteNode->getPreviousColor()->setNextColor(rightMostDeleteNode->getNextColor());
			rightMostDeleteNode->getNextColor()->setPreviousColor(leftMostDeleteNode->getPreviousColor());

			int count = m_colorInfo[leftMostDeleteNode->getPiece()->getColor()].getNumberOfElements();
			m_colorInfo[leftMostDeleteNode->getPiece()->getColor()].setNumberOfElements(count - m_upletSize);
		}
	}
	else if (side == Side::RIGHT) {
		if (rightMostDeleteNode == leftMostDeleteNode->getPreviousColor())
		{
			// cas 1 - tous les pieces de cette couleur seront supprimer dans cette uplet
			m_colorInfo[leftMostDeleteNode->getPiece()->getColor()].setNumberOfElements(0);
			m_colorInfo[leftMostDeleteNode->getPiece()->getColor()].setFirstElement(nullptr);
		}
		else
		{
			// cas 2 - il existe encore des pieces de cette couleur dans le plateau
			leftMostDeleteNode->getPreviousColor()->setNextColor(rightMostDeleteNode->getNextColor());
			rightMostDeleteNode->getNextColor()->setPreviousColor(leftMostDeleteNode->getPreviousColor());

			m_colorInfo[leftMostDeleteNode->getPiece()->getColor()].setFirstElement(leftMostDeleteNode->getPreviousColor());

			int count = m_colorInfo[leftMostDeleteNode->getPiece()->getColor()].getNumberOfElements();
			m_colorInfo[leftMostDeleteNode->getPiece()->getColor()].setNumberOfElements(count - m_upletSize);
		}
	}
}

void Plateau::updateColorUpletForms(Node*& leftMostDeleteNode, Node*& rightMostDeleteNode) {
	bool updatedSquare = false;
	bool updatedTriangle = false;
	bool updatedCircle = false;
	bool updatedRhombus = false;

	Node* current = leftMostDeleteNode;
	while (current != rightMostDeleteNode->getNextNode())
	{
		Form form = current->getPiece()->getForm();

		if (!updatedCircle && form == Form::CIRCLE || (updatedCircle && m_formInfo[form].getFirstElement() == current && form == Form::CIRCLE))
		{
			updateDeletedForms(current, leftMostDeleteNode, rightMostDeleteNode);
			updatedCircle = true;
		}
		if (!updatedSquare && form == Form::SQUARE || (updatedSquare && m_formInfo[form].getFirstElement() == current && form == Form::SQUARE))
		{
			updateDeletedForms(current, leftMostDeleteNode, rightMostDeleteNode);
			updatedSquare = true;
		}
		if (!updatedRhombus && form == Form::RHOMBUS || (updatedRhombus && m_formInfo[form].getFirstElement() == current && form == Form::RHOMBUS))
		{

			updateDeletedForms(current, leftMostDeleteNode, rightMostDeleteNode);
			updatedRhombus = true;
		}
		if (!updatedTriangle && form == Form::TRIANGLE || (updatedTriangle && m_formInfo[form].getFirstElement() == current && form == Form::TRIANGLE))
		{
			updateDeletedForms(current, leftMostDeleteNode, rightMostDeleteNode);
			updatedTriangle = true;
		}

		current = current->getNextNode();
	}
}

void Plateau::updateFormUpletForms(Side side, Node*& leftMostDeleteNode, Node*& rightMostDeleteNode)
{
	if (side == Side::LEFT)
	{
		if (leftMostDeleteNode->getPreviousForm() == rightMostDeleteNode)
		{
			// cas 1 - tous les pieces de cette couleur seront supprimer dans cette uplet
			m_formInfo[leftMostDeleteNode->getPiece()->getForm()].setNumberOfElements(0);
			m_formInfo[leftMostDeleteNode->getPiece()->getForm()].setFirstElement(nullptr);
		}
		else
		{

			// cas 2 - il existe encore des pieces de cette couleur dans le plateau
			leftMostDeleteNode->getPreviousForm()->setNextForm(rightMostDeleteNode->getNextForm());
			rightMostDeleteNode->getNextForm()->setPreviousForm(leftMostDeleteNode->getPreviousForm());

			// update colorsInfo list
			m_formInfo[leftMostDeleteNode->getPiece()->getForm()].setFirstElement(leftMostDeleteNode->getPreviousForm());
			int count = m_formInfo[leftMostDeleteNode->getPiece()->getForm()].getNumberOfElements();
			m_formInfo[leftMostDeleteNode->getPiece()->getForm()].setNumberOfElements(count - m_upletSize);
		}
	}
	else if (side == Side::RIGHT)
	{
		if (rightMostDeleteNode == m_formInfo[rightMostDeleteNode->getPiece()->getForm()].getFirstElement())
		{
			// cas 1 - tous les pieces de cette form seront supprimer dans cette uplet
			m_formInfo[leftMostDeleteNode->getPiece()->getForm()].setNumberOfElements(0);
			m_formInfo[leftMostDeleteNode->getPiece()->getForm()].setFirstElement(nullptr);
		}
		else
		{
			// cas 2 - il existe encore des pieces de cette form dans le plateau
			leftMostDeleteNode->getPreviousForm()->setNextForm(rightMostDeleteNode->getNextForm());
			rightMostDeleteNode->getNextForm()->setPreviousForm(leftMostDeleteNode->getPreviousForm());

			int count = m_formInfo[leftMostDeleteNode->getPiece()->getForm()].getNumberOfElements();
			m_formInfo[leftMostDeleteNode->getPiece()->getForm()].setNumberOfElements(count - m_upletSize);
		}
	}
}

void Plateau::updateFormUpletColors(Node*& leftMostDeleteNode, Node*& rightMostDeleteNode) {
	bool updatedRed = false;
	bool updatedGreen = false;
	bool updatedBlue = false;
	bool updatedYellow = false;

	Node* current = leftMostDeleteNode;
	while (current != rightMostDeleteNode->getNextNode())
	{
		Color color = current->getPiece()->getColor();

		if (!updatedRed && color == Color::RED || (updatedRed && m_colorInfo[color].getFirstElement() == current && color == Color::RED))
		{
			updateDeletedColors(current, leftMostDeleteNode, rightMostDeleteNode);
			updatedRed = true;
		}
		if (!updatedGreen && color == Color::GREEN || (updatedGreen && m_colorInfo[color].getFirstElement() == current && color == Color::GREEN))
		{
			updateDeletedColors(current, leftMostDeleteNode, rightMostDeleteNode);
			updatedGreen = true;
		}
		if (!updatedBlue && color == Color::BLUE || (updatedBlue && m_colorInfo[color].getFirstElement() == current && color == Color::BLUE))
		{
			updateDeletedColors(current, leftMostDeleteNode, rightMostDeleteNode);
			updatedBlue = true;
		}
		if (!updatedYellow && color == Color::YELLOW || (updatedYellow && m_colorInfo[color].getFirstElement() == current && color == Color::YELLOW))
		{
			updateDeletedColors(current, leftMostDeleteNode, rightMostDeleteNode);
			updatedYellow = true;
		}

		current = current->getNextNode();
	}
}

void Plateau::updateDeletedColors(Node* current, Node* leftMostDeleteNode, Node* rightMostDeleteNode)
{
	Color color = current->getPiece()->getColor();

	if (m_colorInfo[color].getNumberOfElements() == 1)
	{
		// cas 1 - la seule piece avec cette form sur le plateau
		m_colorInfo[color].setNumberOfElements(0);
		m_colorInfo[color].setFirstElement(nullptr);
	}
	else if (current->getPreviousColor() == m_colorInfo[color].getFirstElement() && current->getPreviousColor() == rightMostDeleteNode)
	{
		// cas 2 - toutes les pieces de cette forme existe dedent l'uplet a supprimer
		if (isColorUplet(Side::LEFT))
		{
			m_colorInfo[color].setNumberOfElements(0);
			m_colorInfo[color].setFirstElement(nullptr);
		}
		else
		{
			current->getPreviousColor()->setNextColor(current->getNextColor());
			current->getNextColor()->setPreviousColor(current->getPreviousColor());

			m_colorInfo[color].setFirstElement(current->getPreviousColor());
			m_colorInfo[color].decrementNumberOfElements();
		}
	}
	else
	{
		// cas 3 - multiple pieces de cette form dans l'uplet
		// update formInfo
		int numberOfDeltedPieces = 1;
		Node* pieceCounterCursor = current;
		Node* lastDeletedForm = current;

		while (pieceCounterCursor != rightMostDeleteNode)
		{
			pieceCounterCursor = pieceCounterCursor->getNextNode();

			if (pieceCounterCursor->getPiece()->getColor() == color)
			{
				numberOfDeltedPieces++;
				lastDeletedForm = pieceCounterCursor;
			}
		}

		current->getPreviousColor()->setNextColor(lastDeletedForm->getNextColor());
		if (isColorUplet(Side::RIGHT))
		{
			current->getPreviousColor()->setNextColor(m_colorInfo[color].getFirstElement()->getNextColor());
			m_colorInfo[color].getFirstElement()->getNextColor()->setPreviousColor(current->getPreviousColor());
			m_colorInfo[color].setFirstElement(current->getPreviousColor());
		}
		else
		{
			lastDeletedForm->getNextColor()->setPreviousColor(current->getPreviousColor());
		}

		m_colorInfo[color].setNumberOfElements(m_colorInfo[color].getNumberOfElements() - numberOfDeltedPieces);
	}
}

void Plateau::updateDeletedForms(Node* current, Node* leftMostDeleteNode, Node* rightMostDeleteNode)
{
	Form form = current->getPiece()->getForm();

	if (m_formInfo[form].getNumberOfElements() == 1)
	{
		// cas 1 - la seule piece avec cette form sur le plateau
		m_formInfo[form].setNumberOfElements(0);
		m_formInfo[form].setFirstElement(nullptr);
	}
	else if (current->getPreviousForm() == m_formInfo[form].getFirstElement() && current->getPreviousForm() == rightMostDeleteNode)
	{
		// cas 2 - toutes les pieces de cette forme existe dedent l'uplet a supprimer
		if (isColorUplet(Side::LEFT))
		{
			m_formInfo[form].setNumberOfElements(0);
			m_formInfo[form].setFirstElement(nullptr);
		}
		else
		{
			current->getPreviousForm()->setNextForm(current->getNextForm());
			current->getNextForm()->setPreviousForm(current->getPreviousForm());

			m_formInfo[form].setFirstElement(current->getPreviousForm());
			m_formInfo[form].decrementNumberOfElements();
		}
	}
	else
	{
		// cas 3 - multiple pieces de cette form dans l'uplet
		// update formInfo
		int numberOfDeltedPieces = 1;
		Node* pieceCounterCursor = current;
		Node* lastDeletedForm = current;

		while (pieceCounterCursor != rightMostDeleteNode)
		{
			pieceCounterCursor = pieceCounterCursor->getNextNode();

			if (pieceCounterCursor->getPiece()->getForm() == form)
			{
				numberOfDeltedPieces++;
				lastDeletedForm = pieceCounterCursor;
			}
		}

		if (isColorUplet(Side::RIGHT))
		{
			current->getPreviousForm()->setNextForm(m_formInfo[form].getFirstElement()->getNextForm());
			m_formInfo[form].getFirstElement()->getNextForm()->setPreviousForm(current->getPreviousForm());

			m_formInfo[form].setFirstElement(current->getPreviousForm());
		}
		else
		{
			current->getPreviousForm()->setNextForm(lastDeletedForm->getNextForm());
			lastDeletedForm->getNextForm()->setPreviousForm(current->getPreviousForm());
		}

		m_formInfo[form].setNumberOfElements(m_formInfo[form].getNumberOfElements() - numberOfDeltedPieces);
	}
}
