#pragma once
#include "PriorityQueueType.h"
#include <string>
#include "Guest.h"

class GenericRideType
{
private:
	string rideName;									//Name of the Ride
	PriorityQueueType<Guest> rideQueue;					//Queue for the Ride
	double price;										//Price to get on ride (technically price to enter the queue)

public:
	string getRideName()
	{
		return rideName;
	}

	double getPrice()
	{
		return price;
	}

	//Returns the size of the queue
	int getQueueSize()
	{
		return rideQueue.getQueueSize();
	}
	//TODO
	//TODO
	//TODO
	//Maybe add a function to see if a certain guest is in the queue?
	//Some sort of queue functions will be needed
};

