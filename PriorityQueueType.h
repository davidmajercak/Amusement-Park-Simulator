// PriorityQueueType.h
// Author : David Majercak
// Date last edited : 3/10/2020
// Purpose : This class uses a template to create a generic priority queue using a linked list that can be reused in the future.
//		It is based off of the implementation of the queue in the Malik text

//When using templates all functions must be in the header file, as using the .cpp file will cause errors
#pragma once
#include <iostream>
#include <string>

template <class Type>
struct PriorityNodeType
{
	Type info;
	int priority;   //This is what makes it a priority queue (and the additional usage of this variable)
	PriorityNodeType<Type>* link;
};

template <class Type>
class PriorityQueueType
{
private:
	PriorityNodeType<Type>* queueFront;
	PriorityNodeType<Type>* queueRear;
	int queueSize;						//Size of the queue

public:

	PriorityQueueType()
	{
		queueFront = nullptr;
		queueRear = nullptr;
		queueSize = 0;
	}


	//Initializes the queue to an empty state
	void initializeQueue()
	{
		queueSize = 0;
		PriorityNodeType<Type>* temp;
		while (queueFront != nullptr)
		{
			temp = queueFront;
			queueFront = queueFront->link;
			delete temp;
		}

		queueRear = nullptr;
	}


	//Returns True if queue is empty
	//Returns False otherwise
	bool isEmptyQueue() const
	{
		return (queueFront == nullptr);
	}

	//Returns True if queue is full
	//Returns False otherwise
	//This implementation uses a linked list, and is therefore never full
	bool isFullQueue() const
	{
		return false;
	}

	//Returns the front of the Queue
	//If the Queue is empty, gives and error message and returns null
	Type front() const
	{
		if (!isEmptyQueue())
			return queueFront->info;
		else
		{
			std::cout << "Queue is empty, there is nothing to return." << std::endl;
		}
	}

	Type back() const
	{
		if (queueRear != nullptr)
			return queueRear->info;
		else
		{
			std::cout << "Error: Last node in queue is the nullptr." << std::endl;
			return NULL;
		}
	}

	int getQueueSize() const
	{
		return queueSize;
	}

	void addQueue(const Type& newElement, int priority)
	{
		PriorityNodeType<Type>* newNode;
		newNode = new PriorityNodeType<Type>;
		newNode->info = newElement;
		newNode->link = nullptr;
		newNode->priority = priority;

		if (queueFront == nullptr)							//If queue is empty
		{
			queueFront = newNode;
			queueRear = newNode;
		}
		else if (newNode->priority > queueFront->priority)	//If newNode has higher priority than the current head
		{
			newNode->link = queueFront;
			queueFront = newNode;
		}
		else                                                //If newNode will be inserted in the middle (or end) of queue
		{
			PriorityNodeType<Type>* currentNode = queueFront;


			while (currentNode->link != nullptr && currentNode->link->priority >= newNode->priority)
			{
				currentNode = currentNode->link;
			}

			newNode->link = currentNode->link;
			currentNode->link = newNode;
		}

		queueSize++;
	}

	void deleteQueue()
	{
		PriorityNodeType<Type>* temp;

		if (!isEmptyQueue())
		{
			temp = queueFront;
			queueFront = queueFront->link;
			delete temp;
			if (queueFront == nullptr)
				queueRear = nullptr;
			queueSize--;
		}
		else
			std::cout << "Cannot remove from an empty queue" << std::endl;

	}

	~PriorityQueueType()
	{
		PriorityNodeType<Type>* temp;

		while (!isEmptyQueue())
		{
			temp = queueFront;
			queueFront = queueFront->link;
			delete temp;
		}
	}

	void printQueueOfPointers()
	{
		PriorityNodeType<Type>* temp = queueFront;

		if (!isEmptyQueue())
		{
			while (temp != NULL)
			{
				std::cout << *(temp->info);
				temp = temp->link;
			}
		}
	}

	void printQueue()
	{
		PriorityNodeType<Type>* temp = queueFront;

		if (!isEmptyQueue())
		{
			while (temp != NULL)
			{
				std::cout << temp->info;
				temp = temp->link;
			}
		}
	}
};