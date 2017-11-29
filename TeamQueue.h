#pragma once
#pragma once

template <class T>
class TeamQueue
{
public:
	TeamQueue<T>();
	TeamQueue<T>(const TeamQueue<T>&);
	~TeamQueue<T>();

	void enqueue(T, int);
	void dequeue();

	void printQueue();

	class Node
	{
	public:
		Node();
		Node(const Node*);
		~Node();
		T data;
		int team;
		Node * next;
	};
private:
	Node * head;
	Node * end;
};

