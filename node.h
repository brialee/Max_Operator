//Brian Lee
//CS202 - Fant
//Program 1




//Header file for the stopData, stop and streetCar classes.
//A stop is a stopData plus more, and a streetCar is a stop plus more.



#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;

//Constants
const char none[5] = "none";	//used as default name for stop w/o name given


//stopData class.
class stopData 
{
	public:
		stopData(); //constructor
		~stopData();	//destructor
		stopData(const stopData &);	//copy constructor

		//Displays protected members of stopData class.
		//OUTPUT: displays name, stopID and track statuses
		void display();

		//Displays condensed version of stopData
		//OUTPUT: name and stopID
		void displayLight();

		//Sets the name of stopID
		//INPUT: char for name and int for stopID
		//POSTCON: stopData name will be set to name, and stopID set to int passed
		void setName(char [], int);


		//Changes the track status for a given stop
		//INPUT: int for the specific track and bool for track value
		//POSTCON: Track int will have boolean value of passed bool
		void changeTrackStatus(int, bool);


		//Returns the status for requested track
		//INPUT: track to request status for
		//OUTPUT: returns status of request track
		bool trackStatus(int);

	protected:
		char *name;	//name of stop
		int stopID;	//stopID, ex.101
		bool track1;	//true means the track is occupied
		bool track2;	//false means the track is open for a car
		
};



//Stop class which is stopData and more
class stop : public stopData 
{
	public:
		stop();	//constructor
		stop(char [], int);	//constructor with argument for name and stopID
		stop(const stop &);	//copy constructor
		~stop();	//destructor

		//Set next ptr
		//INPUT: stop pointer
		//POSTCON: next will point to passed stop
		//OUTPUT: returns value of passed stop
		bool setNext(stop* &);


		//Set previous ptr
		//INPUT: stop pointer
		//POSTCON: previous will point to passed stop
		//OUTPUT: returns value of passed stop
		bool setPrevious(stop* &);


		//Moves stop to stop -> next
		//INPUT: stop pointer
		//OUTPUT: returns true if ptr was able to move to ptr -> next
		//POSTCON: if true, ptr = ptr -> next, otherwise ptr remains unaltered
		bool moveNext(stop* &);


		//Moves stop to stop -> previous
		//INPUT: stop pointer
		//OUTPUT: returns true if ptr was able to move to ptr -> previous
		//POSTCON: if true, ptr = ptr -> previous, otherise ptr is unaltered
		bool movePrevious(stop* &);


		//Makes a copy of stopID
		//INPUT: int 
		//POSTCON: passed int argument is now equal to the stopID
		void copyID(int &);


		//Deallocates stop data
		//POSTCON: next and previous are set to null
		void deallocateStop();

	protected:
		stop *next;	//pointer to next stop
		stop *previous;	//pointer to previous stop

};




//streetCar class. A streetCar is a stop plus more!
class streetCar
{
	public:
		streetCar();	//constructor
		streetCar(char id[], stop* &loc);	//constructor with argument for name and location
		streetCar(const streetCar &);	//copy constructor


		//Sets carID
		//INPUT: char array
		//POSTCON: carID is now equal to passed char array
		void setID(char []);

		//Displays streetCar data
		//OUTPUT: displays stop info, carID, and other protected members
		void display();

		//A condensed version of the display() function
		//OUTPUT: Displays condensed stopData and carID
		void displayLight();

		//Switches track
		//POSTCON: A streetCar on track1 will now be on track2
		void switchTrack();

		//Set direction for streetCar
		//INPUT: int for direction, 1 - next, 2 - previous
		//POSTCON: Direction set to passed argument
		void setDirection(int);

		//Set track car is on
		//INPUT: int for track
		//POSTCON: streetcar is now on same track as passed argument
		void setTrack(int);


		//Set the location of a streetCar
		//INPUT: stop pointer
		//OUTPUT: Returns true if stop was located and location set
		//POSTCON: location now points to loc. 
		bool setLocation(stop *loc);


		//Change inService value to opposite of current state
		//OUTPUT: return new value of inService
		//POSTCON: inService value is changed to opposite initial value
		bool changeService();

		//Checks the location stopID
		//INPUT: a stopID
		//OUTPUT: Returns true if the streetCar has a matching stopID for location
		bool checkID(char []);

		//Change the pace for a car
		//INPUT: int for desired pace
		//POSTCON: pace for car changed to passed argument
		void changePace(int );

		//Traverse to next stop
		//INPUT: 1 for visual mode
		//OUTPUT: if in visual mode, displays current stop as car is traversing
		//POSTCON: Car is now at its "next" stop
		void traverseRoute(int v=0);

		//Get the current location of the car
		//INPUT: stop pointer
		//POSTCON: pointer passed as argument points to current location
		void getLocation(stop* &);


		//OUTPUT: total number of stops that car has made
		int stopsMade();


		//OUTPUT: displays a message to simulate a car moving along a track
		void travel();

		//OUTPUT: displays a message to simulate a car dropping off passengers
		void dropOff();

		//Destructor
		~streetCar();

		//Deallocates data
		//POSTCON: location is null and carID data deallocated
		void deallocateCar();	

	protected:
		stop *location; //current location of car
		char *carID;	//name of car
		bool inService;	//true if car is inService
		int pace, direction, track;	//direction: 1-next, 2-previous, track is either 1-2
		int max_passengers, total_passengers, num_stops;

		//INPUT track the car should switch two
		//POSTCON: car is now on requested track
		//OUTPUT: return value of current track
		int switchTrack(int);

		//INPUT: stop pointer, track, direction and pace ints
		//OUTPUT: returns true if the track is clear ahead for pace number of stops
		bool checkPacing(stop*, int, int, int);


		//INPUT: stop pointer, track, direction and visual mode ints
		//OUTPUT: If in visual mode, stops will appear as the car arrives at them
		//POSTCON: car location will be set to "next" stop
		int traverseRoute(stop* &, int, int, int);

};
