#include "TeamQueue.h"


template <class T>
TeamQueue<T>::TeamQueue() : head(nullptr), end(nullptr)
{
}

template <class T>
TeamQueue<T>::TeamQueue(const TeamQueue<T>& other)
{
	if (other.head != nullptr)
	{
		head = new Node(other.head);
		Node* current = other.head;
		end = head;
		while (current->next != nullptr)
		{
			end->next = new Node(current->next);
			end = end->next;
			current = current->next;
		}
	}

}


template <class T>
TeamQueue<T>::~TeamQueue()
{
	Node * current = head;
	Node * nxt = head->data;
	while (current->next != nullptr)
	{
		delete current;
		current = nxt->next;
		nxt = current->next;
	}
	head = nullptr;
	end = nullptr;
}



template <class T>
TeamQueue<T>::Node::Node()
{
	previous = next = nullptr;
	team = 0;
}

template <class T>
TeamQueue<T>::Node::Node(const Node* other)
{
	data = other->data;
	team = other->team;
}

template <class T>
TeamQueue<T>::Node::~Node()
{
	delete next;
	next  = nullptr;
}
