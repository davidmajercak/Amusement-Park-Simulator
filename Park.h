// Park.h
// Author : David Majercak
// Date last edited : 5/16/2020
// Purpose : This class was not actually used for the project, but will probably be used if I expand the project in the future

#pragma once
#include <string>

class Park
{
private:
	double admission;			//Price of admission, each Guest must pay this amount when they enter the park
	double fastPassCost;		//Price of the fastPass (for WealthyGuests)
	std::string parkName;			//Name of the Park
	double popularity;			//How popular the park is, represents how likely it is that a new Guest will enter the park

public:
	double getAdmission()
	{
		return admission;
	}

	std::string getParkName()
	{
		return parkName;
	}


};

