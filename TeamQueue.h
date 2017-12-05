/* Shady Boukhary
TeamQueue.h	*/

#pragma once
#include <string>

template <class T>
struct Node
{
	// contructors

	Node();
	Node(T, int);
	Node(const Node*);

	// Member data

	T data;
	int team;
	Node<T> * next;
};


template <class T>
class TeamQueue
{
	typedef Node<T> Node;
public:

	// Constructors

	TeamQueue();
	TeamQueue(const TeamQueue<T>&);
	~TeamQueue();

	// Predicates

	bool isEmpty() const;

	// Mutators

	void enqueue(T, int);
	std::string dequeue();

	// Accessors

	int search(int) const;
	std::string to_string(int, T, int x) const;
	std::string to_string() const;
	int getNum() const;

private:
	Node * head;
	Node * tail;
	int num;
};



#include "TeamQueue.cpp"