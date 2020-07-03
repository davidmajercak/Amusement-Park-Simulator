// SetType.h
// Author : David Majercak
// Date last edited : 2/28/2020
// Purpose : This creates a sorted Set  

#pragma once

template <class T>
class SetType
{
private:
	struct Node
	{
		T data;
		Node* next;
	};

	Node* head;
	int count;
public:
	//Default constructor
	SetType()
	{
		head = NULL;
		count = 0;
	}

	//Destructor calls clear() to free up the memory used for the Nodes
	~SetType()
	{
		std::cout << "Destructor has been called" << std::endl;
		clear();
	}

	//Returns the current size of the Set
	int getSize()
	{
		return count;
	}

	//Returns true if the set is empty
	//Returns false if the set is NOT empty
	bool isEmpty()
	{
		return (head == NULL);
	}

	//Returns true if data is found in the Set
	//Returns false if data is not found
	bool search(T data)
	{
		Node* temp = head;

		//if temp->data > data, we know it is not in the set since the set is sorted
		while (temp != NULL || temp->data > data)
		{
			if (temp->data == data)
				return true;
			temp = temp->next;
		}
		return false;
	}

	//Inserts data into the Set in sorted order, as long as the data is not already in the Set(no duplicates)
	//Increments count if new data is inserted
	void insert(T data)
	{
		Node* temp = new Node;
		temp->data = data;
		temp->next = NULL;

		//If list is empty 
		if (head == NULL)
		{
			head = temp;
			std::cout << "Adding first entry of " << data << " to list. " << std::endl;
		}
		else
		{
			std::cout << "Adding new element " << data << " to list. " << std::endl;
			Node* current; //iterator
			current = head;

			//If data is already the head of the list
			if (data == current->data)
				return;
			if (data < current->data)
			{
				temp->next = head;
				head = temp;
			}
			else
			{
				while (current->next != NULL)
				{
					//if already exists
					if (data == current->next->data)
						return;
					//Insert into the set
					if (data < current->next->data)
					{
						temp->next = current->next;
						current->next = temp;
						break;
					}
					current = current->next;
				}

				//Insert at the end of the Set
				if (current->next == NULL)
				{
					current->next = temp;
				}
			}
		}
		count++;
	}

	//Outputs the List
	//Mostly for Debugging purposes
	void printList()
	{
		if (head == NULL)
		{
			std::cout << "No nodes to print!" << std::endl;
		}
		else
		{
			Node* current;
			current = head;

			while (current != NULL)
			{
				std::cout << current->data << std::endl;
				current = current->next;
			}
		}
	}

	//If the data exists, deletes that node
	void erase(T data)
	{
		Node* temp = NULL;
		Node* current = head;

		//Delete the head of the Set
		if ((head != NULL) && (data == head->data))
		{
			temp = head;
			head = head->next;
			delete temp;
			temp = NULL;
			std::cout << "Deleted " << data << std::endl;
		}
		else
		{
			while (current != NULL)
			{
				if (current->data == data)
				{
					std::cout << "Deleting " << data << std::endl;
					temp = current->next;
					current->next = current->next->next;
					delete temp;
					temp = NULL;
					count--;
					break;			//Break is needed only if you only want to delete 1 occurrence of T data each time delete() is called
				}
				else if (current->data > data)
				{
					std::cout << "Node not found in set, nothing to delete" << std::endl;
					return;
				}
				current = current->next;
			}
		}
	}

	//Purges all information from the set
	//	This function is used for the destructor
	void clear()
	{
		Node* temp = NULL;

		while (head != NULL)
		{
			//cout << "Deleting " << head->data << endl;
			temp = head;
			head = head->next;
			delete temp;
		}

		count = 0;
	}
};
