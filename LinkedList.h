#pragma once

template <class T>
class LinkedList
{
private:
	struct Node
	{
		T data;
		Node* next;
	};

	Node* head;
	Node* tail;
	int count;
public:
	LinkedList()
	{
		head = NULL;
		tail = NULL;
		count = 0;
	}

	~LinkedList()
	{
		clear();
	}

	T front()
	{
		return head->data;
	}
	void clear()
	{
		Node* temp = NULL;

		while (head != NULL)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
		count = 0;
	}

	void Delete(T dataToDelete)
	{
		Node* temp = head;

		if (head == NULL)		//Nothing to delete
			return;
		if (head->data == dataToDelete)
		{
			head = head->next;
			delete temp;
		}
		else
		{
			while (temp->next != NULL)	//If data in middle of linked list
			{
				if (temp->next->data == dataToDelete)
				{
					Node* temp2 = temp->next;
					temp->next = temp->next->next;
					delete temp2;
				}
				temp = temp->next;
			}
			if (temp->data == dataToDelete)	//if data at end of linked list
				delete temp;
		}

		count--;
	}

	void insert(T data)
	{
		Node* newNode = new Node;
		newNode->data = data;
		newNode->next = head;
		head = newNode;
		count++;
	}

	bool find(T value)
	{
		Node* temp = head;

		if(head == NULL)
			return false;
		else
		{
			while (temp != NULL)
			{
				if (temp == value)
					return true;
				temp = temp->next;
			}
			return false;
		}
	}

	//Returns an object in the linked list by it's name if it exists in the linked list
	//Only works for objects that have a getName() method
	T retrieveObjectByName(string name)
	{
		Node* temp = head;

		if (head != NULL)
		{
			while (temp != NULL)
			{
				if (temp->data->getName() == name)
					return temp->data;
				temp = temp->next;
			}
		}
		return NULL;
	}

	//Returns an object in the linked list by it's index in the Linked List
	T retrieveByIndex(int index)
	{
		if (head != NULL)
		{
			Node* temp = head;
			for (int i = 0; i < index; i++)
			{
				//TODO
				//TODO
				//Figure out what exactly is happening that sometimes with 3+ coasters it will rarely point to null
				if(temp->next != NULL)		
					temp = temp->next;
			}

			return temp->data;

		}
		
		return NULL;
	}

	void printLinkedListOfPointers()
	{
		if (count == 0)
		{
			std::cout << "The Linked List is Empty, nothing to print" << endl;
			return;
		}

		Node* temp = head;
		
		for (int i = 0; i < count; i++)
		{
			std::cout << *(temp->data);
			temp = temp->next;
		}

	}

	//Returns the number of items in the Linked List
	int getSize()
	{
		return count;
	}
};