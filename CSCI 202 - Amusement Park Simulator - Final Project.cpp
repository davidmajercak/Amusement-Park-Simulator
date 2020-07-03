// CSCI 202 - Amusement Park Simulator - Final Project.cpp
// Author : David Majercak
// Date last edited : 5/16/2020
// Purpose : The main class for the Amusement Park Simulator Project

#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "SetType.h"
#include "QueueType.h"
#include "Guest.h"
#include "GenericStoreType.h"
#include "RollerCoaster.h"


using namespace std;


string userName;                                        //Name of the User
string amusementParkName;                               //Name of the Amusement Park
string userInput;                                       //used for latest user input
double userInputDouble;                                 //used for user input in the case of Doubles
int userInputInt;                                       //used for user input in the case of Integers
double currentTime;                                     //used to space out loop updates
int tickRate = 600;                                     //Time between loops in milliseconds
int idleGuestActions = 1;                               //Number of Actions that Guests can take each Tick (base is 1)
bool gameOver = false;                                  //Used to determine when to Quit Game
QueueType<Guest*> idleGuests;                           //A Queue that holds idleGuests (Guests which are not in any Queue, not on any ride, not in any shop)
LinkedList<GenericStoreType*> stores;                   //Linked List of stores in the park
LinkedList<RollerCoaster*> rollerCoasters;              //Linked List of Roller Coasters in the park

int turnsToSkip = 0;                                    //How many turns the User has elected to skip (max of 50)
double parkAttrictiveness = 1;                          //Value used to determine how likely it is more Guests will come to the park
int currentGuestCount = 0;                              //Current number of Guests in the Park
double currentMoney = 4000;                             //Money that the user currently has, can be spent on park features
int guestNumberRunningTotal = 0;                        //Total number of Guests that have entered the park (including Guests that have left)
int tickNumberRunningTotal = 0;                         //Total number of Ticks this game

int numRollerCoasters = 0;                              //Number of Roller Coasters in the Park

static void gameMenu();
static void generateGuest();
static void idleGuestUpdate();
static void guestTakeAction(Guest* guest);
static void guestPayMoney(Guest* guest, double cost);
static void rollerCoasterUpdate();

int main()
{
    cout << "Welcome to Amusement Park Simulator (Basically Roller Coaster Tycoon Lite)" << endl;
    cout << "What is your name? : " << endl;
    getline(cin, userName);

    cout << "What do you want to name your Amusement Park?:" << endl;
    getline(cin, amusementParkName);

    cout << "Good luck running " << amusementParkName << ", " << userName << "!" << endl;
    cout << "I recommend building a roller coaster first, then skipping some turns to make some more money!" << endl;
    cout << "It is also a good idea to add more carts to coasters once their queue starts staying full!" << endl;

    cout << "Enter '0' for the help screen" << endl;

    currentTime = GetTickCount();     //This implementation only supports windows systems, some other solution would be needed in a production environment

    while (!gameOver)
    {
        if (GetTickCount() - currentTime >= tickRate)
        {
            tickNumberRunningTotal++;
            currentTime = GetTickCount();       //Reset the timer so that the games loop has pauses in between
                                                //Placing this at beginning of the loop instead of at the end so that pauses are felt more
                                                //      when skipping turns rather than when playing a turn at a time

            //TODO 
            //TODO
            //TODO
            //If price is too high, Guest will get back into Queue or Leave park
            //Break up gameMenu() into smaller Methods
            //Implement isAngry() for Guests
            //This boolean determines when a Guest leaves the Park
            //Make sure to check for isAngry() somewhere in the loop to make sure Guests are leaving properly
            //Due to not having enough money or potentially other reasons?
            //Implement Unique Guests / Celebrities
            //create a bool for unique Guests
            //Posse or papparazzi joins the park x ticks after the guest appears
            //Create a notifications section of the menu

            cout << "\n-------------------------------------------- Tick #" << to_string(tickNumberRunningTotal)  << " --- Park Owner: " << userName << " --- Park Name :  " << amusementParkName <<  " --------------------------------------------" << endl;
            cout << amusementParkName << " has " << currentGuestCount << " guests currently in the park and has $" << currentMoney << endl;

            if (turnsToSkip == 0)                                                                   //If User is not skipping turns
                gameMenu();
            else                                                                                    //Else decrement number of turns to skip
            {
                turnsToSkip--;
                cout << "The next " << turnsToSkip << " Ticks will be skipped by you" << endl;
            }

            generateGuest();                    //Rolls for if a new Guest will enter the Park and adds them to Idle Queue if generated

            idleGuestUpdate();                  //Updates the Guests at the front of the Idle Queue

            rollerCoasterUpdate();              //Updates Roller Coasters, and their Queue and Carts



            if (gameOver)
                break;

            cout << "~~~IDLE GUESTS~~~" << endl;
            if (currentGuestCount > 0)
                idleGuests.printQueueOfPointers();
            else
                cout << "There are currently no Guests in your Park... you should build something!" << endl;
            if (numRollerCoasters != 0)
            {
                for (int i = 0; i < numRollerCoasters; i++)
                {
                    cout << "\n~~~" << rollerCoasters.retrieveByIndex(i)->getName() << "~~~" << endl;
                    rollerCoasters.retrieveByIndex(i)->print();
                }
            }
        }
    }
    if(idleGuests.getQueueSize() > 0)
        idleGuests.deleteQueue();



    cout << "Thank you for playing!" << endl;
    system("pause");
    return 0;
}

//Menu for the game
static void gameMenu()
{
    while (true)
    {
        cout << "What do you want to do? (Press Enter for done entering actions)" << endl;
        cout << "Enter '0' for help/tips" << endl;
        cout << "Enter '1' to view/change/upgrade current Roller Coasters" << endl;
        cout << "Enter '2' to build a roller coaster" << endl;
        cout << "Enter '3' to change Guest names (only Guests in the Idle Queue can have names changed)" << endl;
        cout << "Enter '9' to skip turns (you will decide how many Ticks to skip up to 50)" << endl;
        cout << "Enter '-1' to quit the program" << endl;

        getline(cin, userInput);

        if (userInput == "0")
        {
            //Print Help
            cout << "~~~~~General Help~~~~~\n" << endl;
            cout << "Each in game \"Tick\" there is a chance that a guest will enter your park" << endl;
            cout << "Building more Roller Coasters will make it more likely that guests will enter your park (about 10 more guests per roller coaster)" << endl;
            cout << "Guests are first placed into the Idle Queue" << endl;
            cout << "When Guests make it to the front of the Idle Queue, a \"Roll\" is made to determine which action they will take" << endl;
            cout << "If a Guests decides to ride a Roller Coaster, they will enter the Priority Queue for that Roller Coaster" << endl;
            cout << "Guests will pay the price of entry for the Roller Coaster upon entering its Priority Queue" << endl;
            cout << "The Priority Queue for each Ride is with respect to wealth level (randomly generated for each Guest)" << endl;
            cout << "Wealthier Guests will be placed into the Queue in front of those with a lower Wealth Level, but behind those with equal Wealth Level already in the Queue" << endl;
            cout << "When a Guest makes it to the front of the Priority Queue for the Roller Coaster, they are placed on the Cart that is at the \"Station\"" << endl;
            cout << "\"Wait Time Ticks\" determines how many Ticks the Roller Coaster will wait for the Cart to fill up with Guests before sending it on the Roller Coaster" << endl;
            cout << "Default value for Wait Time Ticks is 10.  It is usually not a good idea to change this, but if you do, the Cart will also leave the Station upon being full" << endl;
            cout << "Capacity for Carts is set to 5 for all Carts" << endl;
            cout << "When the Cart leaves the Station, it's Guests will stay on the Cart until the ride is over (Number of Ticks for Ride Length cannot be changed)" << endl;
            cout << "When the Cart returns to the Station, all of the Guests on the Cart will be returned to the Idle Queue in 1 tick" << endl;
            cout << "Only 1 Guest can get into a Cart Each Tick from the Ride's Queue, although the number of Guests that can enter a Ride Queue each turn" << endl;
            cout << "         can be increased with the number of Guests currently in your Park" << endl;
            cout << "If there is more than one Cart for your Roller Coaster, the Guests on it will have to wait for their Cart to return to the Station to" << endl;
            cout << "         return to the Idle Queue" << endl;
            cout << endl;
            cout << "~~~~~Tips~~~~~\n" << endl;
            cout << "Build Roller Coasters to increase the amount of Guests in your park" << endl;
            cout << "Increasing the amount of Guests in your park increases the number of Guests that can take an action from the Idle Queue each turn (+1 action per 10 guests in your park)" << endl;
            cout << "Add more Carts to Roller Coasters when your Roller Coaster Queues fill up faster than they can empty" << endl;
            cout << "Change Guests names (from the Idle Queue only) to keep track of your favorite Guests!" << endl;
            cout << "Enter '9' on the menu to skip up to 50 turns to more quickly earn money (you won't get stopped on the menu each tick)" << endl;
            cout << "When viewing your Roller Coasters, you can increase the price to earn money faster (max price $20)" << endl;
            cout << "There is a small time delay in between each tick (about 1 second)" << endl;
            cout << "There is a 1% chance each time a Guest gets on a Roller Coaster that they will get angry and start heading for the park exit" << endl;
            cout << endl;


        }
        else if (userInput == "1")          //View Current Roller Coasters
        {

            if (numRollerCoasters == 0)
            {
                cout << "You haven't built any Roller Coasters yet..." << endl;
                cout << "You should build one!" << endl;
            }
            else
            {
                cout << "~~~List of Roller Coasters~~~" << endl;

                rollerCoasters.printLinkedListOfPointers();

                cout << endl;

                cout << "Enter the name of the Roller Coaster you would like to modify (case sensitive and space sensitive):" << endl;
                getline(cin, userInput);

                if (rollerCoasters.retrieveObjectByName(userInput) != NULL)
                {
                    RollerCoaster* rollerCoasterPtr = rollerCoasters.retrieveObjectByName(userInput);

                    cout << "Options for " << rollerCoasterPtr->getName() << ":" << endl;
                    cout << "Enter '1' to change the name of this Roller Coaster" << endl;
                    cout << "Enter '2' to change the price" << endl;
                    cout << "Enter '3' to purchase another cart for this Roller Coaster" << endl;
                    cout << "Enter '4' to set Wait Time Ticks Max (Maximum number of ticks to wait for cart to fill)" << endl;

                    getline(cin, userInput);

                    if (userInput == "1")                //Change name of Roller Coaster
                    {
                        cout << "Enter a new name for " << rollerCoasterPtr->getName() << endl;

                        getline(cin, userInput);
                        rollerCoasterPtr->setName(userInput);

                        cout << "Roller Coaster has been renamed to " << rollerCoasterPtr->getName() << endl;
                    }
                    else if (userInput == "2")           //Change Price of Coaster
                    {
                        cout << "Enter the new price for " << rollerCoasterPtr->getName() << endl;
                        cout << "Current price for " << rollerCoasterPtr->getName() << " is $" << rollerCoasterPtr->getPrice() << endl;

                        while (!(cin >> userInputDouble) || userInputDouble < 0)
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');

                            cout << "Price must be a positive number" << endl;
                        }

                        cin.clear();
                        cin.ignore(1000, '\n');

                        if (userInputDouble > 20)
                        {
                            cout << "Maximum price for Roller Coasters is $20" << endl;
                            userInputDouble = 20;
                        }
                        else if (userInputDouble < 5)
                        {
                            cout << "Minimum price for Roller Coasters is $5" << endl;
                            userInputDouble = 5;
                        }

                        rollerCoasterPtr->setPrice(userInputDouble);
                        cout << "Price for " << rollerCoasterPtr->getName() << " has been set to $" << rollerCoasterPtr->getPrice() << endl;
                    }
                    else if (userInput == "3")      //Add another Cart to the Roller Coaster
                    {
                        cout << rollerCoasterPtr->getName() << " currently has " << rollerCoasterPtr->getNumCarts() << " carts" << endl;
                        cout << "Add another cart for $" << ((rollerCoasterPtr->getNumCarts()) * 500) << "?" << endl;
                        cout << "Enter \"Y\" or \"y\" to purchase: " << endl;

                        getline(cin, userInput);

                        if ((userInput == "Y" || userInput == "y") && currentMoney > (rollerCoasterPtr->getNumCarts()) * 500)
                        {
                            currentMoney -= ((rollerCoasterPtr->getNumCarts()) * 500);
                            rollerCoasterPtr->addCart();

                            cout << "Cart #" << rollerCoasterPtr->getNumCarts() << " successfully added to " << rollerCoasterPtr->getName() << endl;
                        }
                        else
                        {
                            if (currentMoney >= (rollerCoasterPtr->getNumCarts()) * 500)
                                cout << "You don't have enough money for this!" << endl;
                            cout << "You have decided not to add another Cart to " << rollerCoasterPtr->getName() << endl;
                        }
                    }
                    else if (userInput == "4")      //Change Wait Time Ticks Max for Roller Coaster
                    {
                        cout << "Enter the new wait time ticks for " << rollerCoasterPtr->getName() << endl;
                        cout << "Current wait time ticks for " << rollerCoasterPtr->getName() << " is " << rollerCoasterPtr->getWaitTimeTicksMax() << endl;

                        while (!(cin >> userInputInt) || userInputInt < 0)
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');

                            cout << "Wait Time Ticks must be a positive integer" << endl;
                        }

                        cin.clear();
                        cin.ignore(1000, '\n');


                        rollerCoasterPtr->setWaitTimeTicksMax(userInputInt);
                        cout << "Wait Time Ticks for " << rollerCoasterPtr->getName() << " has been set to " << rollerCoasterPtr->getWaitTimeTicksMax() << endl;
                    }
                }
                else
                {
                    cout << "Sorry, a Roller Coaster named \"" << userInput << "\" does not exist in your park. (case sensitive and space sensitive)" << endl;
                }
            }
        }
        else if (userInput == "2")          //Build another Roller Coaster
        {

            cout << "Add another Roller Coaster for $" << 1000 * (double)(numRollerCoasters + 1) << "?" << endl;
            cout << "Enter \"Y\" or \"y\" to purchase: " << endl;

            getline(cin, userInput);

            if ((userInput == "Y" || userInput == "y"))
            {
                if (currentMoney >= (1000 * ((double)numRollerCoasters + 1)))
                {
                    currentMoney -= (1000 * ((double)numRollerCoasters + 1));
                    numRollerCoasters++;

                    rollerCoasters.insert(new RollerCoaster(numRollerCoasters));

                    cout << "You built " << rollerCoasters.front()->getName() << "!" << endl;
                    if (numRollerCoasters == 1)
                        cout << "Congratulations of building your first Roller Coaster!" << endl;

                    parkAttrictiveness += 10;
                }
                else
                {
                    cout << "Sorry, you need $" << to_string(1000 * (numRollerCoasters + 1)) << " to purchase your next Roller Coaster. " << endl;
                }
            }
            else
            {
                cout << "You cancelled building another Roller Coaster" << endl;
            }
        }
        else if (userInput == "3")          //Change Guest Names
        {
            cout << "Here is the list of Guests in the Idle Queue" << endl;
            if (currentGuestCount != 0)
            {
                idleGuests.printQueueOfPointers();
                cout << "Enter the Guests name you would like to change (case sensitive and space sensitive):" << endl;

                getline(cin, userInput);
                if (idleGuests.retrieveObjectByName(userInput) != NULL)
                {
                    Guest* temp = idleGuests.retrieveObjectByName(userInput);
                    cout << "What would you like to rename " << temp->getName() << " to? : " << endl;
                    getline(cin, userInput);
                    if (userInput != "")
                    {
                        temp->setName(userInput);

                        cout << "Guest has been renamed to " << temp->getName() << endl;
                    }
                    else                        //Prevent user from accidentally renaming a guest ""
                    {
                        cout << "Empty string is not a valid guest name" << endl;
                    }
                }
                else
                {
                    cout << "Sorry, a Guest named \"" << userInput << "\" does not exist in your park. (case sensitive)" << endl;
                }
            }

            else
            {
                cout << "No Guests to rename" << endl;
            }
        }
        else if (userInput == "9")
        {
            cout << "How many Ticks would you like to skip? (between 1 and 50) : " << endl;
            cout << "This will also end your current turn" << endl;

            while (!(cin >> userInputInt) || userInputInt < 0 || userInputInt > 50)
            {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "Turns to Skip must be a positive Integer no greater than 50" << endl;
            }

            cin.clear();
            cin.ignore(1000, '\n');

            turnsToSkip = userInputInt;

            cout << "The next " << to_string(turnsToSkip) << " Ticks will occur without showing the menu" << endl;
            break;                  //End current turn

        }
        else if (userInput == "-1")
        {
            gameOver = true;
            break;
        }
        else
        {
            break;                  //Exit loop and resume game
        }
    }
    

}

static void generateGuest()
{
    if (currentGuestCount < parkAttrictiveness)
    {
        if ((rand() % 10 + 1) > 4)        //if current guest count is less than park attractiveness * 10 then it is very likely for guests to join
        {
            idleGuests.addQueue(new Guest(guestNumberRunningTotal));
            cout << idleGuests.back()->getName() << " entered your park!" << endl;
            currentGuestCount++;
            guestNumberRunningTotal++;
            cout << "There are now " << currentGuestCount << " Guests in " << amusementParkName << "!" << endl;
        }
    }
    else
    {
        if ((rand() % 100 + 1) > 95)  //Otherwise very low chance (about 5%)
        {
            cout << "Consider upgrading park attractiveness by building roller coasters to get more guests to join your park" << endl;
            idleGuests.addQueue(new Guest(guestNumberRunningTotal));
            cout << idleGuests.back()->getName() << " entered your park!" << endl;
            currentGuestCount++;
            guestNumberRunningTotal++;
            cout << "There are now " << currentGuestCount << " Guests in " << amusementParkName << "!" << endl;
        }
    }
}

static void idleGuestUpdate()
{
    idleGuestActions = 1;              //Number of Guests in IdleGuests who take an action per game tick

    if (currentGuestCount > 10)    //Number of IdleGuest actions starts at 1 and increases every 10 guests
    {
        idleGuestActions += (currentGuestCount / 10);            //Update number of Guests than can take an action each Tick
    }

    while (!idleGuests.isEmptyQueue() && idleGuestActions > 0)          
    {
        if (idleGuests.front()->getCurrentMoney() < 20 || idleGuests.front()->getIsAngry())  //Leave the Park when money gets too low or when angry
        {
            Guest* tempGuest = idleGuests.front();
            idleGuests.deleteQueue();
            cout << tempGuest->getName() << " ran out of money (or got angry) and left the park!" << endl;
            delete tempGuest;
            currentGuestCount--;
        }
        else
        {
  
            guestTakeAction(idleGuests.front());                            //Guest is placed into a Ride Queue or other attraction queue, or placed back in the Idle Guest Queue

            idleGuests.deleteQueue();                                       //Remove this Guest from the front of Idle Guest Queue
        }


        idleGuestActions--;
    }
}

//This function determines the action that a Guest will take when it reaches the front of the Idle Queue
static void guestTakeAction(Guest* guest)
{
    if (numRollerCoasters > 0)                                                                        //If there are RollerCoasters
    {
        
        int randomNumber = 0;
        if(numRollerCoasters > 1)
            randomNumber = rand() % (numRollerCoasters);
        
        if (guest->getCurrentMoney() > rollerCoasters.retrieveByIndex(randomNumber)->getPrice() && (rand() % 100 > 0))       // 1/100 chance to get angry any time
        {
            guestPayMoney(guest, rollerCoasters.retrieveByIndex(randomNumber)->getPrice());
            rollerCoasters.retrieveByIndex(randomNumber)->addToRideQueue(guest);
        }
        else
        {
            cout << "Oh no!" << endl;
            cout << guest->getName() << " got angry! They are heading for the park exit! (leaving park on their next action)" << endl;
            guest->setIsAngry();                                                                        //Guest did not have enough money and will leave the Park on their next Turn
            idleGuests.addQueue(guest);
        }
    }
    else
    {
        idleGuests.addQueue(guest);
    }
}

//This method subtracts money from a Guest and adds that money to the User's money
static void guestPayMoney(Guest* guest, double cost)
{
    guest->subtractMoney(cost);
    currentMoney += cost;
}

//This method updates each Roller Coaster that the User owns every Tick
static void rollerCoasterUpdate()
{
    if (numRollerCoasters > 0)
    {
        for (int i = 0; i < numRollerCoasters; i++)  
        {
            rollerCoasters.retrieveByIndex(i)->update();

            if (rollerCoasters.retrieveByIndex(i)->getCart()->getIsReadyToUnload())
            {
                for (int j = 0; j < rollerCoasters.retrieveByIndex(i)->getCart()->getCurrentGuestsNum(); j++)           //Places each Guest from the Cart into the Idle Queue
                {
                    idleGuests.addQueue(rollerCoasters.retrieveByIndex(i)->getCart()->getGuests()[j]);                  //One at a time but this all occurs in 1 Tick

                }
                rollerCoasters.retrieveByIndex(i)->getCart()->emptyCart();                                              //emptyCart() sets readyToUnload to false and sets currentGuests to 0
                rollerCoasters.retrieveByIndex(i)->resetWaitTimeTicksCurr();                                            //Reset waitTimeTicksCurr so that next Cart has the full amount of time to load
            }
        }
    }
}