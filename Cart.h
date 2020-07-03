#pragma once

#include "LinkedList.h"
#include "Guest.h"

class Cart
{
private:
	string name;					//The name of the Cart (ex. "Cart 1")
	int cartSize;					//The capacity of the Cart, how many Guests it can hold
	int currentGuestsNum;			//Current number of Guests in the Cart
	int ticksToReturn;				//Number of Ticks before the Cart returns to the station (where Guests can load/unload)
	Guest** cart;					//Dynamic array of guest pointers.  The array in which the Guest* are stored.
	bool isReadyToUnload;			//True if Cart has returned to the station and can be unloaded, otherwise False

public:

	~Cart()
	{
		delete[]cart;
	}
	Cart(int cartNumber)
	{
		name = "Cart " + to_string(cartNumber);
		cartSize = 5;		//Default cartSize is 5
		cart = new Guest*[cartSize];
		currentGuestsNum = 0;
		ticksToReturn = 0;
		isReadyToUnload = false;
	}

	std::string getName()
	{
		return name;
	}

	int getCartSize()
	{
		return cartSize;
	}

	void addGuest(Guest* guest)
	{
		cart[currentGuestsNum] = guest;
		currentGuestsNum++;
	}

	Guest** getGuests()
	{
		return cart;
	}

	int getCurrentGuestsNum()
	{
		return currentGuestsNum;
	}

	bool isFull()
	{
		return ((currentGuestsNum) == cartSize);
	}

	bool isCartBack()
	{
		return (ticksToReturn <= 0);
	}

	void sendCartOnRide(int rideTimeTicksMax)
	{
		ticksToReturn = rideTimeTicksMax;
		isReadyToUnload = true;
	}

	int GetTicksToReturn()
	{
		return ticksToReturn;
	}

	void updateTicksToReturn()
	{
		if (ticksToReturn > 0)
			ticksToReturn--;
	}

	//Returns true if Cart can be unloaded and guests put back into idleGuests
	bool getIsReadyToUnload()
	{
		return (isReadyToUnload && ticksToReturn == 0);			//ticksToReturn also needs to be 0 for this to work
	}

	void setIsReadyToUnload(bool newIsReadyToUnload)
	{
		isReadyToUnload = newIsReadyToUnload;
	}

	void emptyCart()
	{
		isReadyToUnload = false;
		currentGuestsNum = 0;
	}
};