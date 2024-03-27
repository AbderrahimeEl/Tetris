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
	delete m_nextPieceToInsert;
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

// Insertion
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

// Deletion
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
		Node* new_tail = m_tail;
		for (int i = 0; i < m_size - m_upletSize; i++)
		{
			new_tail = new_tail->getNextNode();
		}

		new_tail->setNextNode(m_tail->getNextNode());
		m_tail->setNextNode(nullptr);

		m_tail = new_tail;
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

void Plateau::setDeletedNodesBounds(Node** leftMostDeleteNode, Node** rightMostDeleteNode, Side side)
{
	bool isColorUplet = this->isColorUplet(side);

	if (side == Side::RIGHT)
	{
		*rightMostDeleteNode = m_tail;
		*leftMostDeleteNode = m_tail;

		for (int i = 0; i < m_upletSize - 1; i++)
		{
			*leftMostDeleteNode = isColorUplet ? (*leftMostDeleteNode)->getPreviousColor() : (*leftMostDeleteNode)->getPreviousForm();
		}
	}
	else if (side == Side::LEFT)
	{
		*rightMostDeleteNode = m_tail->getNextNode();
		*leftMostDeleteNode = m_tail->getNextNode();

		for (int i = 0; i < m_upletSize - 1; i++)
		{
			*rightMostDeleteNode = isColorUplet ? (*rightMostDeleteNode)->getNextColor() : (*rightMostDeleteNode)->getNextForm();
		}
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

// ColorUplet
void Plateau::updateColorUpletColors(Side side, Node*& leftMostDeleteNode, Node*& rightMostDeleteNode)
{
	Color color = rightMostDeleteNode->getPiece()->getColor();

	if (rightMostDeleteNode == m_colorInfo[color].getFirstElement()
		&& leftMostDeleteNode == m_colorInfo[color].getFirstElement()->getNextColor())
	{
		// cas 1 - tous les pieces de cette couleur seront supprimer dans cette uplet
		m_colorInfo[color].setNumberOfElements(0);
		m_colorInfo[color].setFirstElement(nullptr);
	}
	else
	{
		// cas 2 - il existe encore des pieces de cette couleur dans le plateau
		leftMostDeleteNode->getPreviousColor()->setNextColor(rightMostDeleteNode->getNextColor());
		rightMostDeleteNode->getNextColor()->setPreviousColor(leftMostDeleteNode->getPreviousColor());

		if (side == Side::RIGHT)
		{
			m_colorInfo[color].setFirstElement(leftMostDeleteNode->getPreviousColor());
		}

		int count = m_colorInfo[color].getNumberOfElements();
		m_colorInfo[color].setNumberOfElements(count - m_upletSize);
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

		if (!updatedCircle && form == Form::CIRCLE
			|| (updatedCircle && form == Form::CIRCLE && m_formInfo[form].getFirstElement() == current))
		{
			updateDeletedForms(current, leftMostDeleteNode, rightMostDeleteNode);
			updatedCircle = true;
		}
		if (!updatedSquare && form == Form::SQUARE
			|| (updatedSquare && form == Form::SQUARE && m_formInfo[form].getFirstElement() == current))
		{
			updateDeletedForms(current, leftMostDeleteNode, rightMostDeleteNode);
			updatedSquare = true;
		}
		if (!updatedRhombus && form == Form::RHOMBUS
			|| (updatedRhombus && form == Form::RHOMBUS && m_formInfo[form].getFirstElement() == current))
		{

			updateDeletedForms(current, leftMostDeleteNode, rightMostDeleteNode);
			updatedRhombus = true;
		}
		if (!updatedTriangle && form == Form::TRIANGLE
			|| (updatedTriangle && form == Form::TRIANGLE && m_formInfo[form].getFirstElement() == current))
		{
			updateDeletedForms(current, leftMostDeleteNode, rightMostDeleteNode);
			updatedTriangle = true;
		}

		current = current->getNextNode();
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
	else if (rightMostDeleteNode == m_formInfo[form].getFirstElement()
		&& (current == m_formInfo[form].getFirstElement()->getNextForm() || current->getNextForm() == leftMostDeleteNode))
	{
		// cas 2 - toutes les pieces de cette forme existe dedent l'uplet a supprimer
		if (current == m_formInfo[form].getFirstElement())
		{
			m_formInfo[form].setNumberOfElements(0);
			m_formInfo[form].setFirstElement(nullptr);
		}
	}
	else
	{
		// cas 3 - multiple pieces de cette form dans l'uplet
		// update formInfo
		int numberOfDeletedPieces = 1;
		Node* pieceCounterCursor = current;
		Node* lastDeletedForm = current;

		while (pieceCounterCursor != rightMostDeleteNode)
		{
			pieceCounterCursor = pieceCounterCursor->getNextNode();

			if (pieceCounterCursor->getPiece()->getForm() == form)
			{
				numberOfDeletedPieces++;
				lastDeletedForm = pieceCounterCursor;
			}
		}

		current->getPreviousForm()->setNextForm(lastDeletedForm->getNextForm());
		lastDeletedForm->getNextForm()->setPreviousForm(current->getPreviousForm());

		m_formInfo[form].setFirstElement(current->getPreviousForm());
		m_formInfo[form].setNumberOfElements(m_formInfo[form].getNumberOfElements() - numberOfDeletedPieces);
	}
}

// FormUplet
void Plateau::updateFormUpletForms(Side side, Node*& leftMostDeleteNode, Node*& rightMostDeleteNode)
{
	if (rightMostDeleteNode == m_formInfo[rightMostDeleteNode->getPiece()->getForm()].getFirstElement()
		&& leftMostDeleteNode->getPreviousForm() == m_formInfo[rightMostDeleteNode->getPiece()->getForm()].getFirstElement())
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

		if (Side::RIGHT)
		{
			// update colorsInfo list
			m_formInfo[leftMostDeleteNode->getPiece()->getForm()].setFirstElement(leftMostDeleteNode->getPreviousForm());
		}

		int count = m_formInfo[leftMostDeleteNode->getPiece()->getForm()].getNumberOfElements();
		m_formInfo[leftMostDeleteNode->getPiece()->getForm()].setNumberOfElements(count - m_upletSize);
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

		if (!updatedRed && color == Color::RED
			|| (updatedRed && color == Color::RED && m_colorInfo[color].getFirstElement() == current))
		{
			updateDeletedColors(current, leftMostDeleteNode, rightMostDeleteNode);
			updatedRed = true;
		}
		if (!updatedGreen && color == Color::GREEN
			|| (updatedGreen && color == Color::GREEN && m_colorInfo[color].getFirstElement() == current))
		{
			updateDeletedColors(current, leftMostDeleteNode, rightMostDeleteNode);
			updatedGreen = true;
		}
		if (!updatedBlue && color == Color::BLUE
			|| (updatedBlue && color == Color::BLUE && m_colorInfo[color].getFirstElement() == current))
		{
			updateDeletedColors(current, leftMostDeleteNode, rightMostDeleteNode);
			updatedBlue = true;
		}
		if (!updatedYellow && color == Color::YELLOW
			|| (updatedYellow && color == Color::YELLOW && m_colorInfo[color].getFirstElement() == current))
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
	else if (rightMostDeleteNode == m_colorInfo[color].getFirstElement()
		&& (current == m_colorInfo[color].getFirstElement()->getNextColor() || current->getNextColor() == leftMostDeleteNode))
	{
		// cas 2 - toutes les pieces de cette forme existe dedent l'uplet a supprimer
		if (current == m_colorInfo[color].getFirstElement())
		{
			m_colorInfo[color].setNumberOfElements(0);
			m_colorInfo[color].setFirstElement(nullptr);
		}
	}
	else
	{
		// cas 3 - multiple pieces de cette form dans l'uplet
		// update formInfo
		int numberOfDeletedPieces = 1;
		Node* pieceCounterCursor = current;
		Node* lastDeletedColor = current;

		while (pieceCounterCursor != rightMostDeleteNode)
		{
			pieceCounterCursor = pieceCounterCursor->getNextNode();

			if (pieceCounterCursor->getPiece()->getColor() == color)
			{
				numberOfDeletedPieces++;
				lastDeletedColor = pieceCounterCursor;
			}
		}

		current->getPreviousColor()->setNextColor(lastDeletedColor->getNextColor());
		lastDeletedColor->getNextColor()->setPreviousColor(current->getPreviousColor());

		m_colorInfo[color].setFirstElement(current->getPreviousColor());
		m_colorInfo[color].setNumberOfElements(m_colorInfo[color].getNumberOfElements() - numberOfDeletedPieces);
	}
}

// Shift
bool Plateau::canPerformShift(Color color)
{
	return m_colorInfo[color].getNumberOfElements() >= m_minPiecesForShift;
}

void Plateau::shiftByColor(Color color)
{
	// declarer un pointeur currentColor qui pointe sur le premier element de la couleur a decaler
	Node* currentColor = m_colorInfo[color].getFirstElement();
	Node* newPlacement = m_colorInfo[color].getFirstElement()->getPreviousColor();

	// preparer trois noeuds temporaire pour le decalage read_temp, write_temp et temp pour faire la permutation 
	Node read_temp, write_temp, temp;

	read_temp.setPiece(currentColor->getPiece());
	read_temp.setNextForm(currentColor->getNextForm());
	read_temp.setPreviousForm(currentColor->getPreviousForm());

	// tant que current n'est pas le dernier element de la couleur a decaler
	do {
		// 1. copier les informations(form, nextForm, previousForm) du noeud qui preceed le noeud current dans temp1
		write_temp.setPiece(newPlacement->getPiece());
		write_temp.setNextForm(newPlacement->getNextForm());
		write_temp.setPreviousForm(newPlacement->getPreviousForm());

		// 2. copier la form du current dans currentColor->getPreviosColor().setForm(current->getForm())
		newPlacement->setPiece(read_temp.getPiece());

		// 3. mise a jour de la liste des formes
		Form form = read_temp.getPiece()->getForm();
		if (m_formInfo[form].getNumberOfElements() == 1)
		{
			// cas 1 - il existe une seule piece de cette forme sur le plateau
			// nextForm et previousForm de la forme pointe sur elle meme
			// aucun mise a jour a faire au niveau du pointeur de la forme
			newPlacement->setNextForm(newPlacement);
			newPlacement->setPreviousForm(newPlacement);

			m_formInfo[form].setFirstElement(newPlacement);
		}
		else if (m_formInfo[form].getNumberOfElements() == 2) {
			// cas 2 - il existe deux pieces de cette forme sur le plateau
			newPlacement->setNextForm(read_temp.getNextForm());
			newPlacement->setPreviousForm(read_temp.getPreviousForm());

			// actualiser nextForm et previousForm de l'autre forme pointe sur la nouvelle adresse de la forme
			currentColor->getPreviousForm()->setNextForm(newPlacement);
			currentColor->getPreviousForm()->setPreviousForm(newPlacement);

			// update the first element of the formInfo list
			Node* ptr = currentColor;

			if (newPlacement == m_tail)
			{
				m_formInfo[form].setFirstElement(newPlacement);
			}
			else if (newPlacement == m_tail->getNextNode())
			{
				m_formInfo[form].setFirstElement(newPlacement->getPreviousForm());
			}
			else
			{
				bool isHead = true;

				do {
					ptr = ptr->getNextNode();
					if (ptr->getPiece()->getForm() == newPlacement->getPiece()->getForm() && ptr != currentColor)
					{
						isHead = false;
						break;
					}
				} while (ptr != m_tail);

				if (isHead)
				{
					m_formInfo[form].setFirstElement(newPlacement);
				}
				else
				{
					m_formInfo[form].setFirstElement(newPlacement->getPreviousColor());
				}
			}
		}
		else if (m_formInfo[form].getNumberOfElements() > 2) {
			// cas 3 - il existe plus de deux pieces de cette forme sur le plateau
			Node* formFinderPtr = currentColor;
			do {
				formFinderPtr == currentColor->getNextNode();

				if (formFinderPtr->getPiece()->getForm() == currentColor->getPiece()->getForm()) {
					if (formFinderPtr->getPreviousForm() == currentColor) {
						//	cas 3.1 - si l'order des pieces n'est pas ete modifie
						newPlacement->setNextForm(read_temp.getNextForm());
						newPlacement->setPreviousForm(read_temp.getPreviousForm());

						//	actualiser nextForm et previousForm pour pointer sur la nouvelle adresse de la cette forme
						currentColor->getPreviousForm()->setNextForm(newPlacement);
						currentColor->getNextForm()->setPreviousForm(newPlacement);
					}
					else {
						//	cas 3.2 - si l'order des pieces est modifie
						//	liee les enciens nextForm et previousForm de la forme a decaler entre eux
						currentColor->getPreviousForm()->setNextForm(currentColor->getNextForm());
						currentColor->getNextForm()->setPreviousForm(currentColor->getPreviousForm());

						//	done a la forme a decaler la forme precedente de formFinderPtr
						formFinderPtr->getPreviousForm()->setNextForm(currentColor->getPreviousColor());

						//	done a la forme a decaler la forme suivante formFinderPtr
						newPlacement->setPreviousForm(formFinderPtr->getPreviousForm());

						//	done a la forme precedente de formFinderPtr la forme a decaler
						formFinderPtr->setPreviousForm(currentColor->getPreviousColor());

						//	done a la forme precedente de formFinderPtr la forme a decaler
						newPlacement->setNextForm(formFinderPtr);
					}
					break;
				}
			} while (formFinderPtr != currentColor);

			// update the first element of the formInfo list
			Node* formHeadFinderPtr = m_formInfo[form].getFirstElement();
			Node* lastSeenFormPtr = formHeadFinderPtr;

			do {
				formHeadFinderPtr = formHeadFinderPtr->getNextNode();
				if (formHeadFinderPtr->getPiece()->getForm() == currentColor->getPiece()->getForm() && formHeadFinderPtr != currentColor)
				{
					lastSeenFormPtr = formHeadFinderPtr;
				}
			} while (formHeadFinderPtr != m_tail);

			m_formInfo[form].setFirstElement(lastSeenFormPtr);
		}

		temp = read_temp;
		read_temp = write_temp;
		write_temp = temp;

		currentColor = currentColor->getPreviousColor();
		newPlacement = newPlacement->getPreviousColor();
	} while (currentColor != m_colorInfo[color].getFirstElement());

	read_temp.setPiece(nullptr);
	write_temp.setPiece(nullptr);
	temp.setPiece(nullptr);
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
