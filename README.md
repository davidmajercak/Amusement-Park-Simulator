# Amusement-Park-Simulator
A simulation of an Amusement Park. Guest are attracted to the park when you build roller coasters. Watch guests as they navigate the queues in the park each game tick.

This project was inspired by Roller Coaster Tycoon and was completed as my final project in my Data Structures Class.

General Project Description

My project simulates an amusement park (inspired by Roller Coaster Tycoon).  The user can build roller coasters and add carts to them, as well as watch guests enter and leave the park.  Money can be earned when guests enter the priority queue for the ride, based on their wealth level which is randomly generated upon Guest creation. 
The game is built on ticks which make use of GetTickCount() in Windows.h.  Guests first join the idle queue.  When they reach the front of the idle queue, they can randomly select a roller coaster and enter its queue, or there is a small chance they get upset and head for the park exit (leave on their next action).
There is also a system in which each park you build increases the chance that guests will enter the park (about 10 per roller coaster).  

Approach

I created a menu based program.  First I created the classes that I wanted to use, and then started to populate the classes (roller coaster, guest, cart, etc) with variables and methods.
I based the game on a loop which only occurs once .7 seconds have passed.  I knew I would have to update each ride and each Guest somehow with each tick.  I added features I thought which would be cool or interesting, as well as challenging.


Algorithms

The algorithm that were the hardest to figure out involved the carts for each roller coaster.  I have a maximum amount of time for a cart to wait to fill up before being sent on the ride.  The ride will also go on the ride if it is full.  When a guest is at the front of the ride’s priority queue, if the cart at the front of the cart queue is back (not currently on the track), then the guest is placed into the next seat in the cart.  
Adding new carts was tricky, as I had to place them behind any carts currently back from the ride, but in front of carts currently on the ride.  I also have to cycle the queue to print out the carts and the guests on them, and make sure that the order of the carts is unchanged.  This is also when I would update the ticks to get back from the ride.


I use rand() with different chances to generate a guest wealth level, to decide if a guest would enter the park or not, whether a guest would get angry and leave, etc.  I also keep track of current guests to decide how many actions guests can take.  Only 1 guest can take an action at first, but each 10 guests gives your idle guests one more turn.  However, for each coaster, only one guest can be loaded into a cart each turn.  
I also had to make sure that the priority queue for each roller coaster worked correctly.  Wealthier Guests can ride many more rides as they skip guests with lower wealth levels.  The idle queue is just a regular queue.
There are a lot of algorithms I used for this project, but I think working with roller coasters, carts, and guests makes up the bulk of this (and is the most interesting).


Data Structures
	
Queue – Used for the Idle Queue.  These are regular queues.
A queue is also used to store roller coaster carts.  The cart at the front of the queue is the one that guests will be placed onto.  After a certain amount of ticks, or the cart is full, the cart will be sent on the ride.  Once the ride is over, guests will have to wait until their cart gets back to the front of the queue to be placed back into the Idle Queue.
Priority Queue – Used for roller coaster queues.  Guests of a higher wealth level will be placed in 
front of those with a lower wealth level.
Linked List – Used to store roller coaster.  This way, the user will be able to created as many 
roller coasters as they would like (with enough money).
Array – Used to hold guests who are on roller coaster carts.  The cart can only seat as many 
guests as there are spaces on the cart (currently 5).

Lessons Learned

1. Comments are very important, but they are not everything.  I spent a bunch of time working on this project when it was assigned, then came back to it later.  The comments were very helpful in understanding what else needed to be done.  However, comments are not easily maintained and it was confusing updating comments at times.
2. Skill improves quickly when you give yourself a project.  I think I tried to be a little too ambitious with this project.  There are a lot of things I would do differently if I had started this project again today.  For a start, I would use maps to hold roller coasters.  There is definitely a lot of feature creep with this project.  I started out with an idea and it developed and changed over time.  I wish I had put a bit more thought into how I wanted my project at first.  I am proud of how it turned out but it definitely has become a bit unwieldy.  I would like to look at more open source projects for more ideas on how to structure a project well.
3. There are limits to command line.  In C++, it is not as easy as some other languages to quickly create a GUI.  I think it was challenging to try to display information in this project.  There are a lot of moving pieces and its hard to provide information in an easily readable format in a command line.
4. Data structures are super important.  Getting a bit more familiar with data structures opens up a lot more interesting ways of solving problems.  For example, at first I didn’t know how to store Idle Queues.  I thought I was going to have to iterate through an entire list of guests and update them each turn.  However, storing them in a queue was a great solution.  I only ever had to update guests who were at the front of the queue.  Once I switched to thinking about Idle Guests as in a queue as well, the problem became a lot easier.
5. Take extra care to make sure the program is modular and uses interfaces and methods whenever appropriate.  There were a some really tricky bugs I had to track down while working on this.  A fair bit of the time, I had code doing the same thing, or almost the same thing, in two different places.  Fixing a bug in one spot, and then still having it exist in there other location is frustrating and avoidable.  

