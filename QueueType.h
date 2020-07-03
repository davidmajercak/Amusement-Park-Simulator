//  QueueType.h
// Author : David Majercak
// Date last edited : 3/10/2020
// Purpose : This class uses a template to create a generic queue using a linked list that can be reused in the future.
//		It is based off of the implementation of the queue in the Malik text

//When using templates all functions must be in the header file, as using the .cpp file will cause errors
#pragma once
#include <iostream>
#include <string>

template <class Type>
struct nodeType
{
	Type info;
	nodeType<Type>* link;
};

template <class Type>
class QueueType
{
private:
	nodeType<Type>* queueFront;
	nodeType<Type>* queueRear;
	int queueSize;						//Size of the queue

public:

	QueueType()
	{
		queueFront = nullptr;
		queueRear = nullptr;
		queueSize = 0;
	}


	//Initializes the queue to an empty state
	void initializeQueue()
	{
		queueSize = 0;
		nodeType<Type>* temp;
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
	//If the Queue is empty, gives an error message 
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

	int getQueueSize()
	{
		return queueSize;
	}

	void addQueue(const Type& newElement)
	{
		nodeType<Type>* newNode;
		newNode = new nodeType<Type>;

		newNode->info = newElement;
		newNode->link = nullptr;

		if (queueFront == nullptr)
		{
			queueFront = newNode;
			queueRear = newNode;
		}
		else
		{
			queueRear->link = newNode;		//Add newNode to the end of Queue
			queueRear = newNode;			//Set newNode as the new queueRear
		}

		queueSize++;
	}

	void deleteQueue()
	{
		nodeType<Type>* temp;

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

	~QueueType()
	{
		nodeType<Type>* temp;

		while (!isEmptyQueue())
		{
			temp = queueFront;
			queueFront = queueFront->link;
			delete temp;
		}
	}

	void printQueueOfPointers()
	{
		nodeType<Type>* temp = queueFront;

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
		nodeType<Type>* temp = queueFront;

		if (!isEmptyQueue())
		{
			while (temp != NULL)
			{
				std::cout << temp->info;
				temp = temp->link;
			}
		}
	}

	//Returns an object in the linked list by it's name if it exists in the linked list
	//Only works for objects that have a getName() method

	Type retrieveObjectByName(std::string name)
	{
		nodeType<Type>* temp = queueFront;

		if (queueFront != NULL)
		{
			while (temp != NULL)
			{
				if (temp->info->getName() == name)
					return temp->info;
				temp = temp->link;
			}
		}
		return NULL;
	}
};