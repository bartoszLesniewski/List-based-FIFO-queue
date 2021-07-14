#include <iostream>
#include "Queue.h"

Queue::Queue()
{
	begin = nullptr;
	end = nullptr;

	front = nullptr;
	back = nullptr;
	nextFront = nullptr;
	nextBack = nullptr;
	listSize = 0;
}

Queue::~Queue()
{
	while (begin != nullptr)
		delBeg();
}

Node* Queue::xorPointers(Node* n1, Node* n2) const
{
	return (Node*)((uintptr_t)n1 ^ (uintptr_t)n2);
}

void Queue::updateQueueAfterAdd(Node* tmp)
{
	if (front == begin && front != back)
		nextFront = tmp;
}

void Queue::addBeg(int newValue)
{
	if (begin == nullptr)
	{
		begin = new Node;
		begin->xorPtr = nullptr;
		begin->value = newValue;
		end = nextBack = begin;
	}

	else
	{
		Node* tmp = new Node;
		tmp->xorPtr = begin;
		tmp->value = newValue;
		begin->xorPtr = xorPointers(tmp, begin->xorPtr);

		if (back == begin)
			nextBack = tmp;

		updateQueueAfterAdd(tmp);

		begin = tmp;
	}

	listSize++;
}

void Queue::addEnd(int newValue)
{
	if (end == nullptr)
		addBeg(newValue);
	else
	{
		Node* tmp = new Node;
		tmp->xorPtr = end;
		tmp->value = newValue;
		end->xorPtr = xorPointers(tmp, end->xorPtr);

		if (back == begin)
			nextBack = tmp;

		updateQueueAfterAdd(tmp);

		end = tmp;
		listSize++;
	}
}

void Queue::updateQueueAfterDel(Node* tmp)
{
	if (front == tmp && back == tmp)
	{
		front = back = nextFront = nullptr;
		nextBack = end;
	}
	else
	{
		if (nextFront == tmp)
			nextFront = end;
		
		if (nextBack == tmp)
			nextBack = end;

		if (front == tmp)
		{
			front = end;
			if (end->xorPtr != nullptr && front != back)
				nextFront = end->xorPtr;
		}

		if (back == tmp)
			back = begin;
	}
}

void Queue::delBeg()
{
	if (begin != nullptr)
	{
		Node* tmp = begin;
		begin = begin->xorPtr;

		if (begin != nullptr)
			begin->xorPtr = xorPointers(tmp, begin->xorPtr);

		if (end == tmp)
			end = begin;

		listSize--;

		updateQueueAfterDel(tmp);

		delete tmp;
	}
}

void Queue::delEnd()
{
	if (end != nullptr)
	{
		Node* tmp = end;
		end = end->xorPtr;

		if (end != nullptr)
			end->xorPtr = xorPointers(tmp, end->xorPtr);

		if (begin == tmp)
			begin = end;

		listSize--;

		updateQueueAfterDel(tmp);

		delete tmp;
	}
}

void Queue::print(printOption opt) const
{
	Node* previousNode = nullptr, * currentNode, * tmp;

	if (opt == FORWARD)
	{
		currentNode = begin;
		tmp = begin;
	}
	else
	{
		currentNode = end;
		tmp = end;
	}

	if (tmp == nullptr)
		std::cout << "NULL";

	else
	{
		while (tmp != nullptr)
		{
			std::cout << tmp->value << " ";
			tmp = xorPointers(previousNode, tmp->xorPtr);
			previousNode = currentNode;
			currentNode = tmp;
		}
	}

	std::cout << std::endl;
}

// Funkcjonalnoœci kolejki
void Queue::movePointer(Node** tmp, Node* prev) const
{
	if (*tmp == begin)
		*tmp = end;
	else if (*tmp == end)
		*tmp = end->xorPtr;
	else
		*tmp = xorPointers((*tmp)->xorPtr, prev);
}

void Queue::editListNode(int newValue)
{
	Node* tmp = back;
	nextBack->value = newValue;
	back = nextBack;

	movePointer(&nextBack, tmp);

	if (front == nullptr)
		front = nextFront = back;
}

void Queue::addNewNode(int newValue)
{
	if (nextBack == nullptr) // lista oraz kolejka s¹ puste
	{
		addBeg(newValue);
		front = back = nextFront = begin;
	}

	else if (nextBack == end)
	{
		addBeg(newValue);
		back = begin;
		nextBack = end;
	}
	else // wpychamy element pomiêdzy front i back
	{
		Node* tmp = new Node;
		tmp->xorPtr = xorPointers(front, back);
		tmp->value = newValue;
		front->xorPtr = xorPointers(xorPointers(front->xorPtr, back), tmp);
		back->xorPtr = xorPointers(xorPointers(back->xorPtr, nextBack), tmp);
		back = tmp;

		listSize++;
	}
}

void Queue::push(int newValue)
{
	if (nextBack != front) // jeœli lista jest d³u¿sza ni¿ kolejka //if (listSize > queueSize)
		editListNode(newValue);

	else
		addNewNode(newValue);

	if (front == nextFront && front != back)
		nextFront = back;
}

void Queue::printQueue() const
{
	if (front != nullptr)
	{
		std::cout << front->value << " ";
		if (nextFront != front)
		{
			Node* currentNode = front;
			Node* nextNode = nextFront;
			Node* tmp = nullptr;

			while (currentNode != back)
			{
				tmp = currentNode;
				currentNode = nextNode;
				movePointer(&nextNode, tmp);

				std::cout << currentNode->value << " ";
			}
		}
	}
	else
		std::cout << "NULL";

	std::cout << std::endl;
}

void Queue::size() const
{
	std::cout << listSize << std::endl;
}

void Queue::count() const
{
	int counter = 0;
	if (front != nullptr)
	{
		counter = 1;
		Node* currentNode = front;
		Node* nextNode = nextFront;
		Node* tmp = nullptr;

		while (currentNode != back)
		{
			counter++;
			tmp = currentNode;
			currentNode = nextNode;
			movePointer(&nextNode, tmp);
		}
	}

	std::cout << counter << std::endl;
}

void Queue::pop()
{
	if (front != nullptr)
	{
		std::cout << front->value << std::endl;

		if (front == back)
		{
			front = back = nextFront = nullptr;
			nextBack = end;
		}

		else
		{
			Node* tmp = front;
			front = nextFront;

			if (nextFront != back)
				movePointer(&nextFront, tmp);
		}
	}
	else
		std::cout << "NULL" << std::endl;
}

void Queue::deleteNode(Node** tmp, Node** previousNode, Node** currentNode)
{
	Node* nodeToDelete = *tmp;
	Node* nextNode = xorPointers(nodeToDelete->xorPtr, *previousNode);
	(*previousNode)->xorPtr = xorPointers(xorPointers((*previousNode)->xorPtr, nodeToDelete), nextNode);
	nextNode->xorPtr = xorPointers(xorPointers(nextNode->xorPtr, nodeToDelete), *previousNode);

	*tmp = nextNode;
	*currentNode = *tmp;

	if (nodeToDelete == nextBack)
		nextBack = *tmp;

	delete nodeToDelete;
	listSize--;
}

void Queue::garbageSoft(Node** tmp, Node** previous, Node** current)
{
	(*tmp)->value = 0;
	if (*tmp == end)
		*tmp = end->xorPtr;
	else if (*tmp == begin)
		*tmp = end;
	else
		*tmp = xorPointers((*tmp)->xorPtr, *previous);

	*previous = *current;
	*current = *tmp;
}

void Queue::garbageHard(Node** tmp, Node** previous, Node** current)
{
	if (*tmp == begin)
	{
		delBeg();
		*tmp = end;
		*current = end;
		*previous = nullptr;
	}
	else if (*tmp == end)
	{
		delEnd();
		*tmp = end;
		*current = end;
		*previous = end->xorPtr;
	}
	else
		deleteNode(tmp, previous, current);
}

void Queue::garbage(garbageOption opt)
{
	if (listSize > 0)
	{
		Node* current, * tmp, * previous;

		tmp = nextBack;
		current = nextBack;
		previous = back;

		while (tmp != front)
		{
			if (opt == SOFT)
				garbageSoft(&tmp, &previous, &current);
			else
				garbageHard(&tmp, &previous, &current);
		}
	}
}