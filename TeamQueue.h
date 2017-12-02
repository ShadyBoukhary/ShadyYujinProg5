#pragma once

#include <string>


template <class T>
struct Node
{
	Node();
	Node(T, int);
	Node(const Node*);
	~Node();
	T data;
	int team;
	Node<T> * next;
};


template <class T>
class TeamQueue
{
	typedef Node<T> Node;
public:
	TeamQueue();
	TeamQueue(const TeamQueue<T>&);
	~TeamQueue();

	bool isEmpty();
	void enqueue(T, int);
	void dequeue();
	int search(int);
	std::string to_string(int);

private:
	Node * head;
	Node * tail;
	int num;
};



#include "TeamQueue.cpp"