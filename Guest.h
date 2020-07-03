// Guest.h
// Author : David Majercak
// Date last edited : 3/5/2020
// Purpose : This class represents guests in the amusement park
//		More specific Guest Types have different values for the behaviors also start out having more money

#pragma once

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Guest
{
private:	
	string name;						//Name of park guest
	double currentMoney;				//Current amound of money in dollars
	int wealthLevel;					//0 wealth level is for standard guests, with richer guests having more money and higher priority in ride queues
										//The following variables are unused
										//Behaviors might be added in a future update to make guests have different chances to perform certain actions
	double lavishnessBehavior;			//Multiplier for likeliness to spend money (1 == 100% chance to buy and 0 == 0% chance)
	double passivenessBehavior;			//Multiplier for likeliness to be passive (1 == will not take any actions and 0 == always takings actions)
	double thrillSeekingBehavior;		//Multiplier for likeliness to choose thrill rides over tame rides (1 == 100% thrill rides and 0 == 100% tame rides)
	double happiness;					//Happiness determines how long a guest will stay in the park, it is decremented with actions like buying things or riding rides
	bool isAngry;						//boolean value that determines if Guest will stay in the Park on their next turn.  If True they will leave the Park on their next turn

	//TODO
	//TODO
	//TODO
	//Create a set of objects guest is interested in buying

public:

	Guest()
	{
		name = "";
		currentMoney = NULL;
		lavishnessBehavior = NULL;
		passivenessBehavior = NULL;
		thrillSeekingBehavior = NULL;
		happiness = NULL;
		wealthLevel = NULL;
		isAngry = false;
	}

	Guest(int guestNumber)
	{
		
		int guestRNG = rand() % 101;

		name = "Guest ";

		//Formatting name so that Names are organized neatly for up to 1000 Guests
		if (guestNumber < 10)
			name += "  ";
		else if (guestNumber < 100)
			name += " ";

		name += to_string(guestNumber);
		
		if (guestRNG == 100)			//Determining wealthLevel for Guest
		{
			wealthLevel = 4;			//about 1/101 chance for wealth level 4
			currentMoney = 5000;		//Higher Wealth level gives guests more money to spend
			lavishnessBehavior = 1;		//Wealth level also determines guest currentMoney
		}								//Also affects lavishnessBehavior
		else if (guestRNG > 95)
		{
			wealthLevel = 3;
			currentMoney = 1500;
			lavishnessBehavior = .75;
		}
		else if (guestRNG > 85)
		{
			wealthLevel = 2;
			currentMoney = 1000;
			lavishnessBehavior = .6;
		}
		else if (guestRNG > 70)
		{
			wealthLevel = 1;
			currentMoney = 500;
			lavishnessBehavior = .5;
		}
		else
		{
			wealthLevel = 0;
			currentMoney = 100;
			lavishnessBehavior = .2;
		}

		passivenessBehavior = rand() % 91 + .05;	//passiveness and thrillseeking are random within range .05 to .95
		thrillSeekingBehavior = rand() % 91 + .05;	
		happiness = 1;								//happiness always starts at 1 :)
		isAngry = false;
	}

	Guest(Guest& other)
	{
		name = other.name;
		currentMoney = other.currentMoney;
		lavishnessBehavior = other.lavishnessBehavior;
		passivenessBehavior = other.passivenessBehavior;
		thrillSeekingBehavior = other.thrillSeekingBehavior;
		happiness = other.happiness;
		wealthLevel = other.wealthLevel;
	}

	string getName() 
	{
		return name;
	}

	double getCurrentMoney()
	{
		return currentMoney;
	}

	void subtractMoney(double cost)
	{
		currentMoney -= cost;
		if (currentMoney < 0)
			currentMoney = 0;
	}

	double getLavishnessBehavior()
	{
		return lavishnessBehavior;
	}

	double getPassivenessBehavior()
	{
		return passivenessBehavior;
	}

	double getThrillSeekingBehavior()
	{
		return thrillSeekingBehavior;
	}

	double getHappiness()
	{
		return happiness;
	}

	int getWealthLevel()
	{
		return wealthLevel;
	}

	friend ostream& operator<<(ostream &os, const Guest &guest)
	{
		os << guest.name << " has $" << std::setw(4) << guest.currentMoney << " and is wealth level "  << guest.wealthLevel << "\n";
		return os;
	}

	void setName(string newName)
	{
		name = newName;
	}

	void setIsAngry()
	{
		isAngry = true;
	}

	bool getIsAngry()
	{
		return isAngry;
	}
};

