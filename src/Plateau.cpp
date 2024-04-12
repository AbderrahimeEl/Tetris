#include "../include/Plateau.hpp"
#include <iostream>

Plateau::Plateau(int max_size)
	: MAX_SIZE(max_size), m_score(0), m_size(0), m_colorInfo(new ColorInfo[4]), m_formInfo(new FormInfo[4])
{
	m_nextPieceToInsert = generateNextPiece();
}

Plateau::Plateau(int max_size, int score, int size, Node *tail, Piece *nextPieceToInsert, ColorInfo *colorInfo, FormInfo *formInfo)
	: MAX_SIZE(max_size), m_score(score), m_tail(tail), m_size(size)
{
}

Plateau::~Plateau()
{
	delete m_tail;
	delete m_nextPieceToInsert;
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

int Plateau::getMaxSize() const
{
	return MAX_SIZE;
}

void Plateau::insertNode(Side side)
{
	if (m_size >= MAX_SIZE || m_size < 0)
	{
		return;
	}

	Node *insertedNode = new Node();
	insertedNode->setPiece(m_nextPieceToInsert);

	Color color = insertedNode->getPiece()->getColor();
	Form form = insertedNode->getPiece()->getForm();

	if (m_size == 0)
	{
		// (1) update nodes list
		m_tail = insertedNode;
		insertedNode->setNextNode(insertedNode);

		// (2) update colors lists
		insertedNode->setNextColor(insertedNode);
		insertedNode->setPreviousColor(insertedNode);

		m_colorInfo[color].setFirstElement(insertedNode);
		m_colorInfo[color].incrementNumberOfElements();

		// (3) update forms lists
		insertedNode->setNextForm(insertedNode);
		insertedNode->setPreviousForm(insertedNode);

		m_formInfo[form].setFirstElement(insertedNode);
		m_formInfo[form].incrementNumberOfElements();

		m_size++;
		m_nextPieceToInsert = generateNextPiece();

		return;
	}

	// (1) update nodes list
	insertedNode->setNextNode(m_tail->getNextNode());
	m_tail->setNextNode(insertedNode);

	if (side == RIGHT)
	{
		m_tail = insertedNode;
	}

	// (2) update colors lists
	if (m_colorInfo[color].getNumberOfElements() == 0)
	{
		m_colorInfo[color].setFirstElement(insertedNode);

		insertedNode->setNextColor(insertedNode);
		insertedNode->setPreviousColor(insertedNode);
	}
	else
	{
		insertedNode->setPreviousColor(m_colorInfo[color].getFirstElement()->getPreviousColor());
		m_colorInfo[color].getFirstElement()->getPreviousColor()->setNextColor(insertedNode);
		insertedNode->setNextColor(m_colorInfo[color].getFirstElement());
		m_colorInfo[color].getFirstElement()->setPreviousColor(insertedNode);

		if (side == LEFT)
		{
			m_colorInfo[color].setFirstElement(insertedNode);
		}
	}

	m_colorInfo[color].incrementNumberOfElements();

	// (3) update forms lists
	if (m_formInfo[form].getNumberOfElements() == 0)
	{
		m_formInfo[form].setFirstElement(insertedNode);

		insertedNode->setNextForm(insertedNode);
		insertedNode->setPreviousForm(insertedNode);
	}
	else
	{
		insertedNode->setPreviousForm(m_formInfo[form].getFirstElement()->getPreviousForm());
		m_formInfo[form].getFirstElement()->getPreviousForm()->setNextForm(insertedNode);
		insertedNode->setNextForm(m_formInfo[form].getFirstElement());
		m_formInfo[form].getFirstElement()->setPreviousForm(insertedNode);

		if (side == LEFT)
		{
			m_formInfo[form].setFirstElement(insertedNode);
		}
	}

	m_formInfo[form].incrementNumberOfElements();

	m_size++;
	this->deleteUplet();

	m_nextPieceToInsert = generateNextPiece();
}

void Plateau::clearNodesList()
{
	// clear nodes list
	Node *current = m_tail;
	for (int i = 0; i < m_size; i++)
	{
		Node *next = current->getNextNode();
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

bool Plateau::canPerformShift()
{
	return m_size <= MAX_SIZE;
}

void Plateau::updateUpletColor(Node *leftUplet, Node *rightUplet)
{
	Color color = leftUplet->getPiece()->getColor();
	Form form;
	int numberOfElements = m_colorInfo[color].getNumberOfElements();

	// Update Colors
	if (numberOfElements == m_upletSize)
	{
		m_colorInfo[color].setFirstElement(nullptr);
		m_colorInfo[color].setNumberOfElements(0);
	}
	else
	{
		rightUplet->getNextColor()->setPreviousColor(leftUplet->getPreviousColor());
		leftUplet->getPreviousColor()->setNextColor(rightUplet->getNextColor());

		if (leftUplet == m_colorInfo[color].getFirstElement())
		{
			m_colorInfo[color].setFirstElement(rightUplet->getNextColor());
		}

		m_colorInfo[color].setNumberOfElements(numberOfElements - m_upletSize);
	}

	// Update Forms
	Node *temp = leftUplet;
	for (int i = 0; i < m_upletSize; i++)
	{
		form = temp->getPiece()->getForm();
		if (m_formInfo[form].getNumberOfElements() == 1)
		{
			m_formInfo[form].setFirstElement(nullptr);
			m_formInfo[form].setNumberOfElements(0);
		}
		else
		{
			temp->getPreviousForm()->setNextForm(temp->getNextForm());
			temp->getNextForm()->setPreviousForm(temp->getPreviousForm());

			if (temp == m_formInfo[form].getFirstElement())
			{
				m_formInfo[form].setFirstElement(temp->getNextForm());
			}

			m_formInfo[form].decrementNumberOfElements();
		}
		temp = temp->getNextNode();
	}
}

void Plateau::updateUpletForm(Node *leftUplet, Node *rightUplet)
{
	Form form = leftUplet->getPiece()->getForm();
	Color color;
	int numberOfElements = m_formInfo[form].getNumberOfElements();

	// Update Forms
	if (numberOfElements == m_upletSize)
	{
		m_formInfo[form].setFirstElement(nullptr);
		m_formInfo[form].setNumberOfElements(0);
	}
	else
	{
		rightUplet->getNextForm()->setPreviousForm(leftUplet->getPreviousForm());
		leftUplet->getPreviousForm()->setNextForm(rightUplet->getNextForm());

		if (leftUplet == m_formInfo[form].getFirstElement())
		{
			m_formInfo[form].setFirstElement(rightUplet->getNextForm());
		}

		m_formInfo[form].setNumberOfElements(numberOfElements - m_upletSize);
	}

	// Update Colors
	Node *temp = leftUplet;
	for (int i = 0; i < m_upletSize; i++)
	{
		color = temp->getPiece()->getColor();
		if (m_colorInfo[color].getNumberOfElements() == 1)
		{
			m_colorInfo[color].setFirstElement(nullptr);
			m_colorInfo[color].setNumberOfElements(0);
		}
		else
		{
			temp->getPreviousColor()->setNextColor(temp->getNextColor());
			temp->getNextColor()->setPreviousColor(temp->getPreviousColor());

			if (temp == m_colorInfo[color].getFirstElement())
			{
				m_colorInfo[color].setFirstElement(temp->getNextColor());
			}

			m_colorInfo[color].decrementNumberOfElements();
		}
		temp = temp->getNextNode();
	}
}

void Plateau::updateUpletColorForm(Node *leftUplet, Node *rightUplet)
{
	Color color = leftUplet->getPiece()->getColor();
	Form form = leftUplet->getPiece()->getForm();
	int numberOfElementsColor = m_colorInfo[color].getNumberOfElements();
	int numberOfElementsForm = m_formInfo[form].getNumberOfElements();

	// Update Colors
	if (numberOfElementsColor == m_upletSize)
	{
		m_colorInfo[color].setFirstElement(nullptr);
		m_colorInfo[color].setNumberOfElements(0);
	}
	else
	{
		rightUplet->getNextColor()->setPreviousColor(leftUplet->getPreviousColor());
		leftUplet->getPreviousColor()->setNextColor(rightUplet->getNextColor());

		if (leftUplet == m_colorInfo[color].getFirstElement())
		{
			m_colorInfo[color].setFirstElement(rightUplet->getNextColor());
		}

		m_colorInfo[color].setNumberOfElements(numberOfElementsColor - m_upletSize);
	}

	// Update Forms
	if (numberOfElementsForm == m_upletSize)
	{
		m_formInfo[form].setFirstElement(nullptr);
		m_formInfo[form].setNumberOfElements(0);
	}
	else
	{
		rightUplet->getNextForm()->setPreviousForm(leftUplet->getPreviousForm());
		leftUplet->getPreviousForm()->setNextForm(rightUplet->getNextForm());

		if (leftUplet == m_formInfo[form].getFirstElement())
		{
			m_formInfo[form].setFirstElement(rightUplet->getNextForm());
		}

		m_formInfo[form].setNumberOfElements(numberOfElementsForm - m_upletSize);
	}
}

void Plateau::clearUplet(Node *leftUplet)
{
	Node *current = leftUplet;
	Node *next;
	for (int i = 0; i < m_upletSize; i++)
	{
		next = current->getNextNode();
		delete current;
		current = next;
	}
}

void Plateau::deleteUplet()
{
	if (m_size < m_upletSize)
	{
		return;
	}

	Node *beforeUplet = m_tail;
	Node *leftUplet = m_tail->getNextNode();
	Node *rightUplet;

	bool isColorUplet;
	bool isFormUplet;
	Side side;
	int i = 1;

	while (i <= m_size - m_upletSize + 1)
	{
		isColorUplet = this->isColorUplet(leftUplet, &rightUplet);
		isFormUplet = this->isFormUplet(leftUplet, &rightUplet);

		if (isColorUplet || isFormUplet)
		{
			if (m_size == m_upletSize)
			{
				clearNodesList();
				return;
			}

			if (rightUplet == m_tail)
			{
				side = RIGHT;
			}
			else
			{
				side = LEFT;
			}

			// Update nodes list
			beforeUplet->setNextNode(rightUplet->getNextNode());
			if (side == RIGHT)
			{
				m_tail = beforeUplet;
			}

			// Update colorInfo and formInfo
			if (isColorUplet && isFormUplet)
			{
				updateUpletColorForm(leftUplet, rightUplet);
			}
			else if (isColorUplet)
			{
				updateUpletColor(leftUplet, rightUplet);
			}
			else if (isFormUplet)
			{
				updateUpletForm(leftUplet, rightUplet);
			}

			// Clear uplet
			clearUplet(leftUplet);

			// Update size
			m_size -= m_upletSize;

			leftUplet = m_tail;
			i = 0;
		}

		beforeUplet = leftUplet;
		leftUplet = leftUplet->getNextNode();
		i++;
	}
}

bool Plateau::isColorUplet(Node *leftUplet, Node **rightUplet)
{
	Node *current = leftUplet;
	Color color = leftUplet->getPiece()->getColor();
	for (int i = 1; i < m_upletSize; i++)
	{
		current = current->getNextNode();
		if (current->getPiece()->getColor() != color)
		{
			return false;
		}
	}
	*rightUplet = current;
	return true;
}

bool Plateau::isFormUplet(Node *leftUplet, Node **rightUplet)
{
	Node *current = leftUplet;
	Form form = leftUplet->getPiece()->getForm();
	for (int i = 1; i < m_upletSize; i++)
	{
		current = current->getNextNode();
		if (current->getPiece()->getForm() != form)
		{
			return false;
		}
	}
	*rightUplet = current;
	return true;
}

void Plateau::shiftByColor(Color color)
{
	if (!canPerformShift())
	{
		return;
	}

	int numberElements = m_colorInfo[color].getNumberOfElements();
	if (numberElements <= 1)
	{
		return;
	}

	Node *current = m_colorInfo[color].getFirstElement();
	Node *next;
	for (int i = 1; i < numberElements; i++)
	{
		next = current->getNextColor();
		swapPiece(current, next, Shift::COLOR);
		current = next;
	}

	this->deleteUplet();
}

void Plateau::shiftByForm(Form form)
{
	if (!canPerformShift())
	{
		return;
	}

	int numberElements = m_formInfo[form].getNumberOfElements();
	if (numberElements <= 1)
	{
		return;
	}

	Node *current = m_formInfo[form].getFirstElement();
	Node *next;
	for (int i = 1; i < numberElements; i++)
	{
		next = current->getNextForm();
		swapPiece(current, next, Shift::FORM);
		current = next;
	}

	this->deleteUplet();
}

void Plateau::swapPiece(Node *node1, Node *node2, Shift shift)
{
	int numberOfElements1, numberOfElements2;
	if (shift == Shift::COLOR)
	{
		if (node1 == m_formInfo[node1->getPiece()->getForm()].getFirstElement())
		{
			m_formInfo[node1->getPiece()->getForm()].setFirstElement(node2);
		}

		if (node2 == m_formInfo[node2->getPiece()->getForm()].getFirstElement())
		{
			m_formInfo[node2->getPiece()->getForm()].setFirstElement(node1);
		}

		numberOfElements1 = m_formInfo[node1->getPiece()->getForm()].getNumberOfElements();
		numberOfElements2 = m_formInfo[node2->getPiece()->getForm()].getNumberOfElements();

		Node *firstNode = (numberOfElements1 == 1) ? node1 : node2;
		Node *secondNode = (numberOfElements1 == 1) ? node2 : node1;

		secondNode->getPreviousForm()->setNextForm(firstNode);
		secondNode->getNextForm()->setPreviousForm(firstNode);

		if (numberOfElements1 == 1 || numberOfElements2 == 1)
		{
			firstNode->setPreviousForm(secondNode->getPreviousForm());
			firstNode->setNextForm(secondNode->getNextForm());
		}
		else
		{
			firstNode->getPreviousForm()->setNextForm(secondNode);
			firstNode->getNextForm()->setPreviousForm(secondNode);

			Node *save = secondNode->getPreviousForm();
			secondNode->setPreviousForm(firstNode->getPreviousForm());
			firstNode->setPreviousForm(save);

			save = secondNode->getNextForm();
			secondNode->setNextForm(firstNode->getNextForm());
			firstNode->setNextForm(save);
		}
	}
	else if (shift == Shift::FORM)
	{
		if (node1 == m_colorInfo[node1->getPiece()->getColor()].getFirstElement())
		{
			m_colorInfo[node1->getPiece()->getColor()].setFirstElement(node2);
		}

		if (node2 == m_colorInfo[node2->getPiece()->getColor()].getFirstElement())
		{
			m_colorInfo[node2->getPiece()->getColor()].setFirstElement(node1);
		}

		numberOfElements1 = m_colorInfo[node1->getPiece()->getColor()].getNumberOfElements();
		numberOfElements2 = m_colorInfo[node2->getPiece()->getColor()].getNumberOfElements();

		Node *firstNode = (numberOfElements1 == 1) ? node1 : node2;
		Node *secondNode = (numberOfElements1 == 1) ? node2 : node1;

		secondNode->getPreviousColor()->setNextColor(firstNode);
		secondNode->getNextColor()->setPreviousColor(firstNode);

		if (numberOfElements1 == 1 || numberOfElements2 == 1)
		{
			firstNode->setPreviousColor(secondNode->getPreviousColor());
			firstNode->setNextColor(secondNode->getNextColor());
		}
		else
		{
			firstNode->getPreviousColor()->setNextColor(secondNode);
			firstNode->getNextColor()->setPreviousColor(secondNode);

			Node *save = secondNode->getPreviousColor();
			secondNode->setPreviousColor(firstNode->getPreviousColor());
			firstNode->setPreviousColor(save);

			save = secondNode->getNextColor();
			secondNode->setNextColor(firstNode->getNextColor());
			firstNode->setNextColor(save);
		}
	}

	Piece *temp = node1->getPiece();
	node1->setPiece(node2->getPiece());
	node2->setPiece(temp);
}