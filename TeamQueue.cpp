#include "TeamQueue.h"
#include <sstream>
#include <iomanip>

template <class T>
TeamQueue<T>::TeamQueue() : head(nullptr), tail(nullptr), num(0)
{}

template <class T>
TeamQueue<T>::TeamQueue(const TeamQueue<T>& other)
{
	if (other.head != nullptr)
	{
		num = other.num;
		head = new Node(other.head);
		Node* current = other.head;
		tail = head;
		while (current->next != nullptr)
		{
			tail->next = new Node(current->next);
			tail = tail->next;
			current = current->next;
		}
	}
}


template <class T>
TeamQueue<T>::~TeamQueue()
{
	if (head->next == nullptr)
		delete head;
	else
	{
		Node * current = head;
		Node * nxt = head->next;
		while (current->next != nullptr)
		{
			delete current;
			current = nxt->next;
			nxt = current->next;
		}
	}
	head = nullptr;
	tail = nullptr;
}

template <class T>
bool TeamQueue<T>::isEmpty()
{
	if (head == nullptr)
		return true;
	else
		return false;
}


template <class T>
int TeamQueue<T>::search(int tm)
{
	int nodeIndex = -1, x = 1;
	
	if (head != nullptr)
	{
		bool found = false;
		Node * current = head;
		while (current != nullptr && !found)
		{
			if (current->team == tm)
			{
				nodeIndex = x;
			}
			current = current->next;
			x++;
		}

	}
	return nodeIndex;
}


template <class T>
void TeamQueue<T>::enqueue(T data, int team)
{
	if (isEmpty())
	{
		head = new Node(data, team);
		tail = head;
	}
	else
	{
		int index = search(team);
		if (index == -1 || index == num)
		{
			tail->next = new Node(data, team);
			tail = tail->next;
		}
		else
		{
			Node * current = head;
			for (int x = 1; x < index - 1; x++)
				current = current->next;
			Node * tmp = new Node(data, team);
			tmp->next = current->next;
			current->next = tmp;
		}
	}
	num++;
}

template <class T>
void TeamQueue<T>::dequeue()
{
	if (isEmpty())
		cout << "\nCannot dequeue from an empty list!\n";
	else if (head == tail)
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		Node * toDelete = head;
		head = head->next;
		delete toDelete;
	}
}

template <class T>
std::string TeamQueue<T>::to_string(int scenario = 0)
{
	std::ostringstream s;			
		/*returns a string of everything in the queue*/
	if (x == 0)
	{
		s << "\n\nCurrently waiting in the Queue:\n"
			<< "------------------------------\n"
			<< "\nID" << std::setw(15) << "TEAM ID\n"
			<< "----" << std::setw(13) << "-------\n";
		Node * current = head;
		while (current != null)
		{
			s << std::left << std::setw(4) << current->data << std::right 
				<< std::setw(10) << current->team << "\n";
			current = current->next;
		}
		s << "\n\n" << "---------\n" << "Total: " << num;
	}
	else if (x == 1)
	{
		s << "\n\nDequeued:\n" << "---------\n"
			<< "\nID" << std::setw(15) << "TEAM ID\n"
			<< "----" << std::setw(13) << "-------\n";
	}
	else
	{
		s << "\n\nComplete Log:\n" << "-------------\n"
			<< "\nEnqueue" << std::setw(15) << "Dequeue\n"
			<< "-------" << std::setw(15) << "-------\n";
	}
	
	return s.str();
	
}

template <class T>
Node<T>::Node()
{
	next = nullptr;
	team = 0;
}


template <class T>
Node<T>::Node(const Node* other)
{
	data = other->data;
	team = other->team;
}

template <class T>
Node<T>::~Node()
{
	delete next;
	next = nullptr;
}

template <class T>
Node<T>::Node(T dat, int tm)
{
	data = dat;
	team = tm;
	next = nullptr;
}