/* Shady Boukhary 
   TeamQueue.cpp	*/

#pragma once
#include "TeamQueue.h"
#include <sstream>
#include <iomanip>



/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
+					TeamQueue()					  +
+ @param none									  +
+ @return none									  +
+ Default contructor for TeamQueue				  +
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

template <class T>
TeamQueue<T>::TeamQueue() : head(nullptr), tail(nullptr), num(0)
{}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
+			TeamQueue(const TeamQueue)			  +
+ @param none									  +
+ @return none									  +
+ Copy contructor for TeamQueue					  +
+ Precondition: other queue not empty			  +
+ Postcondition: deep copy of queue is created    +
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

template <class T>
TeamQueue<T>::TeamQueue(const TeamQueue<T>& other)
{
	// check if other Queue is empty
	if (other.head != nullptr)
	{
		// create a deep copy of head

		num = other.num;
		head = new Node(other.head);
		Node* current = other.head;
		tail = head;

		//loop through the queue and create deep copies of all nodes

		while (current->next != nullptr)
		{
			tail->next = new Node(current->next);
			tail = tail->next;
			current = current->next;
		}
	}
}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
+					~TeamQueue()				  +
+ @param none									  +
+ @return none									  +
+ Destructor for TeamQueue						  +
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

template <class T>
TeamQueue<T>::~TeamQueue()
{
	if (head == nullptr)
		return;

	// if there's only 1 node

	if (head->next == nullptr)
		delete head;
	else
	{

		// shallow copies to traverse linked list

		Node * current = head;
		Node * nxt = head->next;

		// loop through the queue and delete all nodes

		while (current->next != nullptr)
		{
			delete current;
			current = nxt;
			nxt = nxt->next;
		}
	}

	head = nullptr;
	tail = nullptr;


}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
+					isEmpty()					  +
+ @param none									  +
+ @return boolean								  +
+ returns true if the Queue is empty			  +
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

template <class T>
bool TeamQueue<T>::isEmpty() const
{
	if (head == nullptr)
		return true;
	else
		return false;
}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
+					Search(int)					  +
+ @param integer								  +
+ @return integer								  +
+ searches the queue for members of specific 	  +
+ team, returns index of team member closest to   +
+ tail. Returns -1 if no such team exists		  +
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

template <class T>
int TeamQueue<T>::search(int tm) const
{
	int nodeIndex = -1, x = 1;

	if (!isEmpty())
	{
		// shallow copy of head to traverse list

		Node * current = head;

		// loop through the list and find the last team member in queue

		while (current != nullptr)
		{
			if (current->team == tm)
			{
				nodeIndex = x;
			}

			// continue to check next node

			current = current->next;
			x++;
		}

	}

	// -1 if team not found

	return nodeIndex;
}



/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
+						enqueue(T, int)						  +
+ @param templated variable, integer						  +
+ @return none												  +
+ Precondition: none										  +
+ Postcondition: adds node to the end of the queue (tail)	  +
+ unless another team member already is in the queue. If that +
+ is the case, node is added right after last team member	  +
+ (closest to tail)											  +
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

template <class T>
void TeamQueue<T>::enqueue(T data, int team)
{
	// if queue is empty, create node at head

	if (isEmpty())
	{
		head = new Node(data, team);
		tail = head;
	}
	else
	{
		// search for team members if team exists

		int index = search(team);

		// if team does not exist or at the back of the queue,
		// insert new team member at tail of queue

		if (index == -1 || index == num)
		{
			tail->next = new Node(data, team);
			tail = tail->next;
		}
		else
		{
			// if team is somewhere in the middle

			Node * current = head;

			//traverse loop until last team member is reached

			for (int x = 1; x <= index - 1; x++)
				current = current->next;

			// insert new team member directly behind last team member

			Node * tmp = new Node(data, team);
			tmp->next = current->next;
			current->next = tmp;
		}
	}
	num++;
}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
+							dequeue()						  +
+ @param none						 						  +
+ @return none												  +
+ Precondition: queue is not empty							  +
+ Postcondition: removes the node at the front of the queue	  +
+ (head) deletes it											  +
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

template <class T>
std::string TeamQueue<T>::dequeue()
{
	try
	{
		if (isEmpty())
			throw string("\nCannot dequeue from an empty list!\n");

		std::string output = to_string(head->team, head->data, 1);

		if (head == tail)
		{
			delete head;
			head = tail = nullptr;
			num--;
		}
		else
		{
			// delete node in the front of queue
			// assign new head
			// decrement node counter

			Node * toDelete = head;
			head = head->next;
			toDelete->next = nullptr;
			delete toDelete;
			num--;
		}
		return output;
	}
	catch (string message)
	{
		return message;
	}
	
}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
+						to_string(int)						  +
+ @param integer						 					  +
+ @return string											  +
+ Precondition: scenario is a valid one						  +
+ Postcondition: returns a string for printing purposes 	  +
+ depending on scenario number								  +
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

template <class T>
std::string TeamQueue<T>::to_string(int team, T data, int x) const
{
	std::ostringstream s;
	s << "";

	/*returns a string of everything in the queue*/

	if (x == 0)
	{
		s << "\n\nCurrently waiting in the Queue:\n"
			<< "------------------------------\n"
			<< "\nID" << std::setw(15) << "TEAM ID\n"
			<< "----" << std::setw(13) << "-------\n";
		Node * current = head;
		while (current != nullptr)
		{
			s << std::left << std::setw(4) << current->data << std::right
				<< std::setw(10) << current->team << "\n";
			current = current->next;
		}
		s << "\n\n" << "---------\n" << "Total: " << num;
	}
	
	/* returns a string with last dequeued element*/

	else if (x == 1)
	{
		s << std::left << std::setw(4) << data
			<< std::right << std::setw(9) << team << "\n";
	}

	/* returns a string for a complete log of events (dequeue & enqueue) */

	else
	{
		s << "\n\nComplete Log:\n" << "-------------\n"
			<< "\nEnqueue" << std::setw(15) << "Dequeue\n"
			<< "-------" << std::setw(15) << "-------\n";
	}

	return s.str();
}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
+						to_string()							  +
+ @param none							 					  +
+ @return string											  +
+ Precondition: none										  +
+ Postcondition: returns a string for printing purposes 	  +
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
template <class T>
std::string TeamQueue<T>::to_string() const
{
	/* returns a string for dequeueing list header */

	std::ostringstream s;
	s << "\nDequeued:\n" << "---------\n"
		<< "\nID" << std::setw(15) << "TEAM ID\n"
		<< "----" << std::setw(13) << "-------\n";
	return s.str();
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
+					 getNum()					  +
+ @param none									  +
+ @return integer								  +
+ returns the number of nodes in list			  +
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
template <class T>
int TeamQueue<T>::getNum() const
{
	return num;
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
+					 Node()						  +
+ @param none									  +
+ @return none									  +
+ Default contructor for Node					  +
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

template <class T>
Node<T>::Node()
{
	next = nullptr;
	team = 0;
}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
+				 Node(const Node*)				  +
+ @param pointer to a Node						  +
+ @return none									  +
+ Copy contructor for Node						  +
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

template <class T>
Node<T>::Node(const Node* other)
{
	data = other->data;
	team = other->team;
}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
+				 Node(T, int)					  +
+ @param templated variable, integer			  +
+ @return none									  +
+ Parameterized contructor for Node				  +
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

template <class T>
Node<T>::Node(T dat, int tm)
{
	data = dat;
	team = tm;
	next = nullptr;
}