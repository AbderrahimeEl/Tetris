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
	// this->m_colorInfo = colorInfo;
	// m_formInfo =formInfo;
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

void Plateau::insertLeft()
{
	if (m_size >= MAX_SIZE)
	{
		return;
	}


	Node* insertedNode = new Node();
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

void Plateau::insertRight()
{
	if (m_size >= MAX_SIZE)
	{
		return;
	}

	Node* insertedNode = new Node();
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

	// neither one has sufficient number of pieces with same color/form
	if (!(hasMinimumSameColor || hasMinimumSameForm))
	{
		return false;
	}

	// we have sufficient number of pieces with same color/form
	if (side == Side::RIGHT)
	{
		bool isColorUplet = true;
		bool isFormUplet = true;

		if (hasMinimumSameColor)
		{
			Node* temp = m_tail;

			for (size_t i = 0; i < m_upletSize - 1; i++)
			{
				if (temp->getPreviousColor()->getNextNode() == temp)
				{
					temp = temp->getPreviousColor();
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
			Node* temp = m_tail;

			for (size_t i = 0; i < m_upletSize - 1; i++)
			{
				if (temp->getPreviousForm()->getNextNode() == temp)
				{
					temp = temp->getPreviousForm();
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
		bool isColorUplet = true;
		bool isFormUplet = true;

		if (hasMinimumSameColor)
		{

			Node* temp = m_tail->getNextNode();

			for (size_t i = 0; i < m_upletSize - 1; i++)
			{
				if (temp->getNextColor() == temp->getNextNode())
				{
					temp = temp->getNextNode();
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

			Node* temp = m_tail->getNextNode();

			for (size_t i = 0; i < m_upletSize - 1; i++)
			{
				if (temp->getNextForm() == temp->getNextNode())
				{
					temp = temp->getNextNode();
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
	if (side == Side::RIGHT)
	{
		if (m_upletSize == m_size) {
			// clear nodeList
			Node* temp = m_tail;
			for (int i = 0; i < m_size; i++)
			{
				Node* next = temp->getNextNode();
				delete temp;
				temp = next;
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
		else if (m_upletSize < m_size) {
			bool isColorUplet = true;

			for (int i = 0; i < m_upletSize - 1; i++)
			{
				Node* temp = m_tail;
				//if (temp->getPreviousColor()->getPiece()->getColor() != temp->getPiece()->getColor())
				if (temp->getPreviousColor()->getNextNode() != temp)
				{
					isColorUplet = false;
					break;

				}
			}

			// déplacer sur le premier node a supprimer a gauche 
			Node* current = m_tail;

			if (isColorUplet)
			{
				for (int i = 0; i < m_upletSize - 1; i++)
				{
					current = current->getPreviousColor();
				}
			}
			else
			{
				for (int i = 0; i < m_upletSize - 1; i++)
				{
					current = current->getPreviousForm();
				}
			}

			if (isColorUplet) {

				// update colors list
				// if current.getPreviousColor() == tail
				if (current->getPreviousColor() == m_tail)
				{
					// cas 1 - tous les pieces de cette couleur seront supprimer dans cette uplet
					// décrémenter nombreElements de cette couleur par upletSize
					m_colorInfo[current->getPiece()->getColor()].setNumberOfElements(0);

					// set firstElement to nullptr
					m_colorInfo[current->getPiece()->getColor()].setFirstElement(nullptr);
				}
				else {

					// cas 2 - il existe encore des pieces de cette couleur dans le plateau
					// set current.getPreviousColor().setNextColor(tail.getNextColor())
					current->getPreviousColor()->setNextColor(m_tail->getNextColor());

					// set tail.getnextColor().setPreviousColor(current.getPreviousColor())
					m_tail->getNextColor()->setPreviousColor(current->getPreviousColor());

					// update colorsInfo list
					// set firstElement to current.getPreviousColor()
					m_colorInfo[current->getPiece()->getColor()].setFirstElement(current->getPreviousColor());

					// décrémenter nombreElements par upletSize
					int count = m_colorInfo[current->getPiece()->getColor()].getNumberOfElements();
					m_colorInfo[current->getPiece()->getColor()].setNumberOfElements(count - m_upletSize);
				}

				// update form details
				// bool updatedSquare = false, updatedRectangle = false, updatedCircle = false, updatedRhombus = false;
				bool updatedSquare = false;
				bool updatedTriangle = false;
				bool updatedCircle = false;
				bool updatedRhombus = false;

				// while(updatedSquare || updatedRectangle || updatedCircle || updatedRhombus == false)
				Node* temp = current;
				while (temp != m_tail->getNextNode()) {

					// circle
					// if !updatedCircle && current.getForm() == Form::Circle
					if (!updatedCircle && temp->getPiece()->getForm() == Form::CIRCLE) {

						updateDeletedForms(temp, current);
						updatedCircle = true;
					}

					if (!updatedSquare && temp->getPiece()->getForm() == Form::SQUARE) {

						updateDeletedForms(temp, current);
						updatedSquare = true;
					}

					if (!updatedRhombus && temp->getPiece()->getForm() == Form::RHOMBUS) {

						updateDeletedForms(temp, current);
						updatedRhombus = true;
					}

					if (!updatedTriangle && temp->getPiece()->getForm() == Form::TRIANGLE) {

						updateDeletedForms(temp, current);
						updatedTriangle = true;
					}

					temp = temp->getNextNode();
				}
			}
			else
			{
				// update colors list
				// if current.getPreviousColor() == tail
				if (current->getPreviousForm() == m_tail)
				{
					// cas 1 - tous les pieces de cette couleur seront supprimer dans cette uplet
					// décrémenter nombreElements de cette couleur par upletSize
					m_formInfo[current->getPiece()->getForm()].setNumberOfElements(0);

					// set firstElement to nullptr
					m_formInfo[current->getPiece()->getForm()].setFirstElement(nullptr);
				}
				else {

					// cas 2 - il existe encore des pieces de cette couleur dans le plateau
					// set current.getPreviousColor().setNextColor(tail.getNextColor())
					current->getPreviousForm()->setNextForm(m_tail->getNextForm());

					// set tail.getnextColor().setPreviousColor(current.getPreviousColor())
					m_tail->getNextForm()->setPreviousForm(current->getPreviousForm());

					// update colorsInfo list
					// set firstElement to current.getPreviousColor()
					m_formInfo[current->getPiece()->getForm()].setFirstElement(current->getPreviousForm());

					// décrémenter nombreElements par upletSize
					int count = m_formInfo[current->getPiece()->getForm()].getNumberOfElements();
					m_formInfo[current->getPiece()->getForm()].setNumberOfElements(count - m_upletSize);
				}

				// update form details
				// bool updatedSquare = false, updatedRectangle = false, updatedCircle = false, updatedRhombus = false;
				bool updatedRed = false;
				bool updatedGreen = false;
				bool updatedBlue = false;
				bool updatedYellow = false;

				// while(updatedSquare || updatedRectangle || updatedCircle || updatedRhombus == false)
				Node* temp = current;
				while (temp != m_tail->getNextNode()) {

					// circle
					// if !updatedCircle && current.getForm() == Form::Circle
					if (!updatedRed && temp->getPiece()->getColor() == Color::RED) {

						updateDeletedColors(temp, current);
						updatedRed = true;
					}

					if (!updatedGreen && temp->getPiece()->getColor() == Color::GREEN) {

						updateDeletedColors(temp, current);
						updatedGreen = true;
					}

					if (!updatedBlue && temp->getPiece()->getColor() == Color::BLUE) {

						updateDeletedColors(temp, current);
						updatedBlue = true;
					}

					if (!updatedYellow && temp->getPiece()->getColor() == Color::YELLOW) {

						updateDeletedColors(temp, current);
						updatedYellow = true;
					}

					temp = temp->getNextNode();
				}

			}

			// (3) node list 

			Node* new_tail = m_tail;
			for (int i = 0; i < m_size - m_upletSize; i++)
			{
				new_tail = new_tail->getNextNode();
			}

			// update size
			m_size -= m_upletSize;

			// update tail
			new_tail->setNextNode(m_tail->getNextNode());
			m_tail->setNextNode(nullptr);
			m_tail = new_tail;

			// free memory 
			for (int i = 0; i < m_upletSize; i++)
			{
				Node* next = current->getNextNode();
				delete current;
				current = next;
			}

		}
	}
	else
	{
		//leftSide
	}

	// TODO formRightSideUplet
	// TODO Display USING COLORS & LETTERS

}

void Plateau::updateDeletedForms(Node* temp, Node* current) {
	Form form = temp->getPiece()->getForm();
	// if current.getPreviousForm() == current
	if (temp->getPreviousForm() == current) {
		// cas 1 - la seule piece avec cette form sur le plateau 
		// update formInfo 

		// numberOfElement = 0 
		m_formInfo[form].setNumberOfElements(0);
		// first = nullptr
		m_formInfo[form].setFirstElement(nullptr);
	}
	else if (temp == m_formInfo[form].getFirstElement()) {
		// cas le seule qui a cette form dans l'uplet ms il y en a autres autrepart 

		temp->getPreviousForm()->setNextForm(temp->getNextForm());
		temp->getNextForm()->setPreviousForm(temp->getPreviousForm());

		// first = current.getPreviousForm()
		m_formInfo[form].setFirstElement(temp->getPreviousForm());
		m_formInfo[form].decrementNumberOfElements();
	}

	// else if current.getPreviousForm() == m_formInfo[form].getFirstElement()
	else if (current->getPreviousForm() == m_formInfo[form].getFirstElement()) {
		// cas 2 - toutes les pieces de cette forme existe dedent l'uplet a supprimer 

		// update formInfo 
		// numberOfElement = 0 
		m_formInfo[form].setNumberOfElements(0);
		// first = nullptr
		m_formInfo[form].setFirstElement(nullptr);
	}

	// else 
	else {
		// cas 3 
		// update formInfo 
		// numberOfElement -= count elements from current up to the first element
		int numberOfDeltedPieces = 1;
		Node* pieceCounterCursor = temp;

		while (true)
		{
			pieceCounterCursor = pieceCounterCursor->getNextForm();
			numberOfDeltedPieces++;

			if (pieceCounterCursor == m_formInfo[form].getFirstElement())
			{
				break;
			}
		}


		// current.getPreviousForm().setNextForm(firstElement.getNextForm())
		temp->getPreviousForm()->setNextForm(m_formInfo[form].getFirstElement()->getNextForm());
		// firstElement.getNextForm().setPreviousForm(current.getPreviousForm())
		m_formInfo[form].getFirstElement()->getNextForm()->setPreviousForm(temp->getPreviousForm());

		// first = current.getPreviousForm()
		m_formInfo[form].setFirstElement(temp->getPreviousForm());
		m_formInfo[form].setNumberOfElements(m_formInfo[form].getNumberOfElements() - numberOfDeltedPieces);
	}

}


void Plateau::updateDeletedColors(Node* temp, Node* current) {
	Color color = temp->getPiece()->getColor();
	// if current.getPreviousForm() == current
	if (temp->getPreviousColor() == current) {
		// cas 1 - la seule piece avec cette form sur le plateau 
		// update formInfo 

		// numberOfElement = 0 
		m_colorInfo[color].setNumberOfElements(0);
		// first = nullptr
		m_colorInfo[color].setFirstElement(nullptr);
	}
	else if (temp == m_colorInfo[color].getFirstElement()) {
		// cas le seule qui a cette form dans l'uplet ms il y en a autres autrepart 

		temp->getPreviousColor()->setNextColor(temp->getNextColor());
		temp->getNextColor()->setPreviousColor(temp->getPreviousColor());

		// first = current.getPreviousForm()
		m_colorInfo[color].setFirstElement(temp->getPreviousColor());
		m_colorInfo[color].decrementNumberOfElements();
	}

	// else if current.getPreviousForm() == m_formInfo[form].getFirstElement()
	else if (current->getPreviousColor() == m_colorInfo[color].getFirstElement()) {
		// cas 2 - toutes les pieces de cette forme existe dedent l'uplet a supprimer 

		// update formInfo 
		// numberOfElement = 0 
		m_colorInfo[color].setNumberOfElements(0);
		// first = nullptr
		m_colorInfo[color].setFirstElement(nullptr);
	}

	// else 
	else {
		// cas 3 
		// update formInfo 
		// numberOfElement -= count elements from current up to the first element
		int numberOfDeltedPieces = 1;
		Node* pieceCounterCursor = temp;

		while (true)
		{
			pieceCounterCursor = pieceCounterCursor->getNextColor();
			numberOfDeltedPieces++;

			if (pieceCounterCursor == m_colorInfo[color].getFirstElement())
			{
				break;
			}
		}


		// current.getPreviousForm().setNextForm(firstElement.getNextForm())
		temp->getPreviousColor()->setNextColor(m_colorInfo[color].getFirstElement()->getNextColor());
		// firstElement.getNextForm().setPreviousForm(current.getPreviousForm())
		m_colorInfo[color].getFirstElement()->getNextColor()->setPreviousColor(temp->getPreviousColor());

		// first = current.getPreviousForm()
		m_colorInfo[color].setFirstElement(temp->getPreviousColor());
		m_colorInfo[color].setNumberOfElements(m_colorInfo[color].getNumberOfElements() - numberOfDeltedPieces);
	}

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
