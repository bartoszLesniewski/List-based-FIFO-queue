#pragma once
#include "Node.h"

class Queue
{
private:
	Node* begin;
	Node* end;;
	Node* front;
	Node* back;
	Node* nextFront;
	Node* nextBack; // wskazuje na element znajduj¹cy siê za ostatnim elementem kolejki, a jeœli kolejka jest pusta - na ostatni element listy (pierwszy kandydat do nadpisania przy wywo³aniu komendy PUSH)

	int listSize;

public:
	enum printOption
	{
		FORWARD,
		BACKWARD
	};

	enum garbageOption
	{
		SOFT,
		HARD
	};

	Queue();
	~Queue();

	Node* xorPointers(Node* n1, Node* n2) const;
	void addBeg(int newValue);
	void addEnd(int newValue);
	void delBeg();
	void delEnd();
	void print(printOption opt) const;
	void size() const;

	void movePointer(Node** tmp, Node* prev) const;
	void updateQueueAfterAdd(Node* tmp);
	void updateQueueAfterDel(Node* tmp);
	void editListNode(int newValue);
	void addNewNode(int newValue);
	void deleteNode(Node** tmp, Node** previousNode, Node** currentNode);

	void push(int newValue);
	void pop();
	void printQueue() const;
	void count() const;
	void garbage(garbageOption opt);
	void garbageSoft(Node** tmp, Node** previous, Node** current);
	void garbageHard(Node** tmp, Node** previous, Node** current);
};