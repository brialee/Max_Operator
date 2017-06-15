//Brian Lee
//CS202 - Fant
//program1


//Implimentation file for the node.h header
//Contains implimentation details for the stopData, stop
//and streetCar classes


#include "node.h"



//------------- STOPDATA CLASS -------------


//Default constructor
stopData::stopData() : name(NULL), stopID(0), track1(NULL), track2(NULL)
{}




//Function to set the name and stopID
void stopData::setName(char n[], int id)
{
	name = new char[strlen(n) +1];
	strcpy(name, n);

	stopID = id;

}


//Copy constructor
stopData::stopData(const stopData &s)
{
	name = new char[strlen(s.name) +1];
	strcpy(name, s.name);
	
	stopID = s.stopID;

	track1 = s.track1;
	track2 = s.track2;
}




//Destructor to deallocate stop data
stopData::~stopData()
{
	/*
	if(name)
	{
		delete []name;
		name = NULL;
	}
*/
	name = NULL;
}




//Displays stop data
void stopData::display()
{	
	cout << "--------------------" << endl;
	cout << "Stop Name: " << name << endl;
	cout << "Stop ID: " << stopID << endl;
	cout << "Track1: " << track1 << " --- Track2: " << track2 << endl;
	cout << "---------------" << endl;
}





//Displays a shortened verison of stop data. Used for graph::listAllCars()
void stopData::displayLight()
{
	cout << "Stop Name: " << name << " -- Stop ID: " << stopID << endl;
	cout << "--------------------------------------------" << endl;
}




//Function to change the track status for a given stop.
//Takes as argument a number for a track and it's new
//boolean value.
void stopData::changeTrackStatus(int track, bool val)
{
	if(track == 1)
		track1 = val;

	else
		track2 = val;
}




//Function to return the track status for a 
//request track. 
bool stopData::trackStatus(int track)
{
	if(track == 1)
		return track1;

	else
		return track2;

}



// --------------- STOP CLASS -----------------
// A stop is stopData and more

//Constructor
stop::stop(): next(NULL), previous(NULL)
{}



//Copy Constructor
stop::stop(const stop &s) : stopData(s)
{
	next = s.next;
	previous = s.previous;
}


//Constructor with arguments for a name and ID
stop::stop(char n[], int id)
{
	setName(n,id);
	next = previous = NULL;
}



//Destructor
stop::~stop()
{
//	next = NULL;
//	previous = NULL;
}




//Deallocates dynamic data for a stop as
//well as setting next and previous pointers
//to NULL
void stop::deallocateStop()
{

	if(name)
		delete []name;

	name = NULL;
	next = NULL;
	previous = NULL;


}



//Takes as an argument an int that will
//be updated to have the value of the current
//stop's stopID
void stop::copyID(int &id)
{
	id = stopID;
}




//Function to set the next pointer. Return the
//value of the pointer passed as an argument
bool stop::setNext(stop* &link)
{
	next = link;
	return link;
}




//Function to set the previous pointer. Returns
//the value of the pointer passed as an argument
bool stop::setPrevious(stop* &link)
{
	previous = link;
	return link;
}


//Function to take the stop pointer passed as
//an argument and move that pointer to pointer -> next.
//If next is NULL, the function returns NULL.
bool stop::moveNext(stop* &s)
{

	if(s -> next)
	{
		s = s -> next;
		return true;
	}
	
	else
		return false;
}




//Function to take the stop pointer passed as an
//argument and move that pointer to pointer -> previous.
//If previous is NULL, the function returns false.
bool stop::movePrevious(stop* &s)
{

	if(s -> previous)
	{
		s = s -> previous;
		return true;
	}
	
	else
		return false;
}







// ------------ STREETCAR CLASS --------------------
//A streetCar is a stop with more


//Default constructor. 
streetCar::streetCar(): carID(NULL), inService(false), pace(3), max_passengers(100)
{
	total_passengers = num_stops = direction = track = 0;
}



//Constructor with arguments for a carId and stop location
streetCar::streetCar(char id[], stop* &loc) : inService(false), pace(3),  max_passengers(100)
{
	carID = new char[strlen(id) +1];
	strcpy(carID, id);

	location = loc;
	total_passengers = num_stops = direction = track = 0;
}



//Copy Constructor
streetCar::streetCar(const streetCar &sc)
{
	carID = new char[strlen(sc.carID) +1];
	strcpy(carID, sc.carID);

	location = sc.location;
	pace = sc.pace;
	inService = sc.inService;
	max_passengers = sc.max_passengers;
	total_passengers = sc.total_passengers;
	num_stops = sc.num_stops;
	direction = sc.direction;
	track = sc.track;
}



//Switches track between track 1 & 2
void streetCar::switchTrack()
{
	if(track == 1)
		track = 2;
	
	else
		track = 1;
}




// Changes the pace for a given streetcar
void streetCar::changePace(int n)
{
	pace = n;
}


//Change the direction of a streetCar
void streetCar::setDirection(int n)
{
	direction = n;
}




// Returns the new value of inService variable
bool streetCar::changeService()
{
	inService = !inService;
	return inService;
}



//Displays a streetCar's ID, boolean for service
//and stop data for the current location
void streetCar::display()
{
	cout << "\n-------------------" << endl;
	cout << "Car ID: " << carID << " -- " << "In Service: " << inService << endl;
	location -> display(); 	
	cout << "\n";
}




//Displays a condensed version of a streetCar's data
void streetCar::displayLight()
{
	cout << "------------" << endl;
	cout << "Car ID: " << carID << " -- In Service: " << inService << endl;
	location -> displayLight();
}


//Sets a streetCar's ID. Used as part of a
//function that reads in streetCar data 
//from an external file....graph::addCars
void streetCar::setID(char id[])
{
	carID = new char[strlen(id) +1];
	strcpy(carID, id);
}



//Function to set the location of a streetCar to the
//passed stop pointer. Returns value of passed stop pointer
bool streetCar::setLocation(stop *loc)
{
	if(!loc)
		return false;

	location = loc;
	return true;
}



//Destructor
streetCar::~streetCar()
{
//	delete []carID;
//	carID = NULL;
//	location = NULL;
}




//Deallocates dynamic memory for a streetCar as well
//as setting the stop pointer to NULL
void streetCar::deallocateCar()
{
	
	if(carID)	
		delete []carID;

	carID = NULL;
	location = NULL;

}



//Function to check if the passed argument matches the
//carID for a given streetCar. If the argument does match
//the carID, function returns true.
bool streetCar::checkID(char id[])
{
	if(strcmp(carID, id) == 0)
		return true;

	return false;	
}




//Public member function to allow the streetCar to traverse
//for one stop. A v-value of 1 means that data will be displayed (v - visual)
//as the car traverses.
void streetCar::traverseRoute(int v)
{
	num_stops += traverseRoute(location, track, direction, v);
}




//Private member function that does the actual traveral. Takes as
//arguments a pointer to the current stop, a track number, a direction number
//and value to have the function display output if desired (visual mode)
//The function will traverse to the next stop. If there is no next stop,
//the function will cause the streetCar to switch directions and tracks.
//This function also makes use of the checkPacing() function. Returns 1
//if traversal was successful.
int streetCar::traverseRoute(stop* &loc, int t, int d, int v)
{
	if(!inService)
		return 0;

	//track is now occupied
	loc -> changeTrackStatus(t, true);


	//Visual mode
	if(v == 1)
	{
		cout << "Current Stop" << endl;
		loc -> display();
		dropOff();
	}

	//Direction is next	
	if(direction == 1)	
	{
		//Either the car is able to move to its'
		//"next" location, or it is somehow stuck.
		//Either way, the current stop is no longer
		//occupied.
		loc -> changeTrackStatus(t, false);

		if(!checkPacing(loc, t, d, pace + 1))
			return 0;

		//if able to move to next stop
		if(loc -> moveNext(loc))
		{
			return 1;
		}

		//If there is no next stop, the end of the
		//track has been reached, time to switch tracks
		//and move to the previous stop.
		else if (loc -> movePrevious(loc))
		{
			setDirection(2);
			switchTrack();
			return 1;
		}

		//Unable to move to next or previous.
		//something is wrong...
		else
			return 0;
	}

	
	//Direction is previous
	else
	{
		loc -> changeTrackStatus(t, false);
		
		if(!checkPacing(loc, t, d, pace))
			return 0;

		//able to move to previous stop
		if(loc -> movePrevious(loc))
			return 1;

		//There is no previous stop, end
		//of the track must have been reached.
		//Time to turn around
		else if(loc -> moveNext(loc))
		{
			setDirection(1);
			switchTrack();
			return 1;
		}

		//Can't move next or previous...
		//something is wrong.
		else
			return 0;
	}

}




//Function to check the pacing of a streetCar. Takes as arguments
// the current stop, number for a track and direction as well as the
// pace. The function will "traverse" via the stop pointer for pace number
// of stops. If, at all during the traversal, the function encounters a
// track that is not open, or there is not 'next' stop, the funtion will
// return false. Otherwise if the track is clear for pace number of stops
// ahead the function will return true.
bool streetCar::checkPacing(stop* loc, int t, int d, int pace)
{
	if(pace == 0)
		return true;


	//if the track is occupied, return false.
	//This is called upon the first invocation
	//just after the status has been returned to false.
	if(loc->trackStatus(track))
		return false;


	--pace;

	//Direction is next	
	if(direction == 1)	
	{
		
		if(loc -> moveNext(loc))
			return checkPacing(loc, t, d, pace);

		//If there is no next stop, the end of the
		//track has been reached, time to switch tracks
		//and move to the previous stop.
		else if (loc -> movePrevious(loc))
		{
			t = switchTrack(t);
			return checkPacing(loc, t, 2, pace);
		}

	}
	
	//Direction is previous, direction  == 2
	else
	{

		//able to move to previous stop
		if(loc -> movePrevious(loc))
			return checkPacing(loc, t, d, pace);

		//There is no previous stop, end
		//of the track must have been reached.
		//Time to turn around
		else if(loc -> moveNext(loc))
		{
			t = switchTrack(t);
			return checkPacing(loc, t, 1, pace);
		}

	}

	return false;
}





//Function to simulate a streetCar dropping off passengers.
//Function will display a message that takes a total of 3 seconds
//to display. Then the function that invoked dropOff() will continue.
void streetCar::dropOff()
{
	time_t start = time(NULL);
	time_t end;
	int n = 0;

	cout << "Dropping off passengers\n" ;

	while(n < 3)
	{
		end = time(NULL);
		if((end - start) == 1)
		{
			++n;
			cout << ".\n";
			start = time(NULL);
		}

	}
	cout << endl;
}





//Function to simulate a streetCar traveling from one stop
//to another. Function will display a message that takes a total
//of 5 seconds to display. After that the function that invoked 
//travel() will resume.
void streetCar::travel()
{
	time_t start = time(NULL);
	time_t end;
	int n = 0;

	cout << "Streecars moving on track" << endl;

	while(n < 5)
	{
		end = time(NULL);
		if((end - start) == 1)
		{
			++n;
			cout << ".\n";
			start = time(NULL);
		}
	}
}



//Fuction to set a stop pointer , given
//as an argument, to point to the stop that
//the streetcar is currently located at. 
void streetCar::getLocation(stop* &ptr)
{
	ptr = location;
}



//Set the track for a streetcar. Function
//used during the traverseRoute() and checkPacing()
//functions. 
void streetCar::setTrack(int n)
{
	track = n;
}




//Returns the "opposite" track. Function used during
//traverseRoute() and checkPacing().
int streetCar::switchTrack(int n)
{
	if(n == 1)
		return 2;

	else
		return 1;

}



//Return the total number of stops
//a streetcar has made
int streetCar::stopsMade()
{
	return num_stops;
}
