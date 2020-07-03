// RollerCoaster.h
// Author : David Majercak
// Date last edited : 5/16/2020
// Purpose : This class represents Roller Coasters
//			Each Coaster has a queue of carts that can be loaded with guests
//			The cart (and it's associated Guests) cannot be accessed until it returns back to the front of the cart Queue (when it is the front of the ride)

#pragma once
#include "PriorityQueueType.h"
#include <string>
#include "Guest.h"
#include "Cart.h"
#include "QueueType.h"

class RollerCoaster
{
private:
	string name;										//Name of the Ride
	PriorityQueueType<Guest*> rideQueue;				//Queue for the Ride
	double price;										//Price to get on ride (technically price to enter the queue)
	int numCarts;										//Current Number of Carts
	QueueType<Cart*> cartQueue;							//Queue of Carts
	int waitTimeTicksMax;								//How many ticks the Roller Coaster waits to fill the ride before leaving the station
	int waitTimeTicksCurr;								//Wait time for Cart in the front of the queue to leave the station
	int rideTimeTicksMax;								//How many ticks the Roller Coaster takes to complete a lap around the track

public:

	~RollerCoaster()
	{
		rideQueue.deleteQueue();
		cartQueue.deleteQueue();
	}
	RollerCoaster(int rollerCoasterNumber)
	{
		name = "Roller Coaster " + to_string(rollerCoasterNumber);
		price = 10;
		numCarts = 0;
		addCart();
		waitTimeTicksMax = 10;
		waitTimeTicksCurr = waitTimeTicksMax;
		rideTimeTicksMax = 20;
	}

	//Returns the Name of the Roller Coaster
	string getName()
	{
		return name;
	}

	//Sets name to the passed in variable
	void setName(string newName)
	{
		name = newName;
	}

	//Returns the Price of the Roller Coaster
	double getPrice()
	{
		return price;
	}

	//Sets a new Price for the Roller Coaster
	//Defaults to 5 if value is negative
	void setPrice(double newPrice)
	{
		if (newPrice > 0)		
			price = newPrice;
		else
			price = 5;
	}

	//Returns the size of the queue
	int getQueueSize()
	{
		return rideQueue.getQueueSize();
	}

	//Returns the Number of Carts for the Roller Coaster
	int getNumCarts()
	{
		return numCarts;
	}

	//Adds another Cart to the Roller Coaster
	void addCart()
	{

		numCarts++;

		if(numCarts == 1)													//The first Cart can simply be added to the Queue
			cartQueue.addQueue(new Cart(numCarts));
		else if (!cartQueue.front()->isCartBack())							//If none of the Carts are at the Station, we want the new Cart to be placed at the Station (In the front)
		{
			cartQueue.addQueue(new Cart(numCarts));							//Add the Cart to the Queue

			for (int i = 0; i < (numCarts - 1); i++)						//Loop the Queue n-1 times so that the new Cart is at the front 
				getNextCart();
		}
		else
		{
			bool addToQueue = false;										//Used to place the Cart properly in the Cart Queue (behind other Carts at station but in front of Carts on the ride)
			bool addedToQueue = false;

			for (int i = 0; i < (numCarts-1); i++)
			{
				if (cartQueue.front()->isCartBack() && !addedToQueue)		//If a Cart is found to be at the Station, and the next Cart isn't then we can add the new Cart into the Queue
				{
					addToQueue = true;
				}
				else if (addToQueue)
				{
					cartQueue.addQueue(new Cart(numCarts));
					addToQueue = false;
					addedToQueue = true;
				}
				getNextCart();												//We still need to loop the Queue back around
			}

			if (!addedToQueue)												//In the Case that all Carts are already at the Station, add it behind them
				cartQueue.addQueue(new Cart(numCarts));
		}
		waitTimeTicksCurr = waitTimeTicksMax;	//Reset Wait Time Ticks for the new cart
	}

	//Loads the Cart with the passed in Guest*
	//If the Cart is full, the cart leaves the station, and the guest is loaded onto the next cart
	void loadCart(Guest* guest)
	{

		cartQueue.front()->addGuest(guest);

		if (cartQueue.front()->isFull())
			cartLeavesStation();
	}

	//Sends cart on the Ride (sets ride ticks), then the next Cart in the Queue is brought to the front of the queue
	void cartLeavesStation()
	{
		cartQueue.front()->sendCartOnRide(rideTimeTicksMax);
		getNextCart();
	}

	//Returns a pointer to the Cart at the front of the cartQueue
	Cart* getCart()
	{
		return cartQueue.front();
	}

	//Cycles the cart Queue to the next Cart, adds the Cart that was at the front back to the end of the Queue
	void getNextCart()
	{
		cartQueue.addQueue(cartQueue.front());   //Place cart at the end of the Cart Queue
		cartQueue.deleteQueue();				 //Delete the Cart (as it has already been placed in the back
	}

	void print()
	{
		std::cout << rideQueue.getQueueSize() << " guests are waiting in the the Queue" << endl;

		rideQueue.printQueueOfPointers();			//Print the Queue

		cout << endl;

		if (numCarts != 0)
		{
			for (int i = 0; i < numCarts; i++)
			{
				std::cout << cartQueue.front()->getName();
				if (cartQueue.front()->GetTicksToReturn() == 0)
				{
					if (i == 0)					//Only the cart at the front of cartQueue can be loaded with Guests
						std::cout << " is at the station loading Guests for " << waitTimeTicksCurr << " more ticks." << endl;
					else                        //Other Carts are waiting the queue
						std::cout << " is waiting in queue at the station." << endl;
				}
				else
					std::cout << " will return the the station in " << cartQueue.front()->GetTicksToReturn() << " ticks." << endl;

				for (int j = 0; j < cartQueue.front()->getCurrentGuestsNum(); j++)
				{
					std::cout << "    Spot #" << (j + 1) << " " << *(cartQueue.front()->getGuests()[j]); //Need to dereference pointer here to use the ostream override for Guest
				}

				getNextCart();
			}
		}
	}

	int getWaitTimeTicksMax()
	{
		return waitTimeTicksMax;
	}

	void resetWaitTimeTicksCurr()
	{
		waitTimeTicksCurr = waitTimeTicksMax;
	}

	void setWaitTimeTicksMax(int newWaitTimeTicksMax)
	{
		waitTimeTicksMax = newWaitTimeTicksMax;
	}

	int getWaitTimeTicksCurr()
	{
		return waitTimeTicksCurr;
	}

	void update()
	{
		if (rideQueue.getQueueSize() > 0)				//If the queue for the ride is not empty
		{
			if (cartQueue.front()->isCartBack())		//And the queue in the front of the queue is back at the station 
			{
				loadCart(rideQueue.front());			//Load the guest at the front of the queue onto the Cart
				rideQueue.deleteQueue();				//Remove the Guest from the Queue
			}
		}

		if (waitTimeTicksCurr >= 1)
			waitTimeTicksCurr--;
		else
		{				//If Cart is back AND full of guests, or enough ticks have passed (Cart no longer waiting)
			if (cartQueue.front()->isCartBack() && (cartQueue.front()->isFull() || waitTimeTicksCurr == 0))
			{
				cartLeavesStation();
				waitTimeTicksCurr = waitTimeTicksMax;
			}
		}

		for (int i = 0; i < numCarts; i++)
		{
			cartQueue.front()->updateTicksToReturn();

			if(numCarts > 1)
				getNextCart();
		}
			
	}

	int getRideTimeTicksMax()
	{
		return rideTimeTicksMax;
	}

	void addToRideQueue(Guest* guest)
	{
		rideQueue.addQueue(guest, guest->getWealthLevel());
		
	}

	friend ostream& operator<<(ostream& os, const RollerCoaster& rollerCoaster)
	{
		os << rollerCoaster.name << " costs $" << rollerCoaster.price << " has " << rollerCoaster.numCarts << " carts and has " << rollerCoaster.rideQueue.getQueueSize() << " guests in the Queue" << endl;
		return os;
	}

};

