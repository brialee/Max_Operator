//Brian Lee
//CS202 -Fant
//program 1



#include "line.h"

//Implimentation file for the LINE and its' derived classes. 


//--------------- LINE CLASS ------------------
//A base from from which loop and twoWay are derived from
//
//
//



//Default constructor
//initializses max cars to 8 per line, all other variables
//set to zero.
line::line() : max_cars(8), num_cars(0), num_stops(0)
{}



//Constructor with argument for line name
line::line(char n[]) : max_cars(8), num_cars(0), num_stops(0)
{
	lineName = new char[strlen(n) +1];
	strcpy(lineName, n);

}


//Copy Constructor
line::line(line &to_copy)
{
	max_cars = to_copy.max_cars;
	num_cars = to_copy.num_cars;
	num_stops = to_copy.num_stops;
	
	lineName = new char[strlen(to_copy.lineName) +1];
	strcpy(lineName, to_copy.lineName);
}


//Destructor, deallocates memeory used for lineName
line::~line()
{
	delete []lineName;
	lineName = NULL;
}


//Displays all protected data for a line
void line::display()
{
	cout << "_____ LINE INFO _____" << endl;
	cout << "Name: " << lineName << endl;
	cout << "Max cars: " << max_cars << endl;
	cout << "Total cars: " << num_cars << endl;
	cout << "Total Stops: " << num_stops << endl;
}



//-------------- TWO WAY CLASS ----------------
//A class derived from LINE
//
//


//Default constructor
twoWay::twoWay(): head(NULL)
{}



//Constructor with a name for an argument
twoWay::twoWay(char n[]) : line(n)
{
	head = NULL;
}


//Copy Constructor
twoWay::twoWay(twoWay &to_copy) : line(to_copy)
{
	head = to_copy.head;
}


//Destructor which invokes deallocate() on its'
//head pointer, which will recursively dellocate
//all data in the DLL head points to.
twoWay::~twoWay()
{
	deallocate(head);
}



//Recursively deallocates the data
//in the DLL. Upon first invocation, the function
//is passed the line's head pointer.
void twoWay::deallocate(stop* &ptr)
{
	stop *temp = ptr;

	if(ptr -> moveNext(ptr))
	{
		temp -> deallocateStop();
		delete temp;
		temp = NULL;
		deallocate(ptr);
	}

	else
	{
		ptr -> deallocateStop();
		delete ptr;
		ptr = NULL;
	}
}



//Read in stop data fron an external text file, "stoplist.txt"
//The function will read the the text file until a matching line
//name is encountered. If it is, then a stops name and stopID
//is read in from the file and used to populate a stop pointer
//which is then added to the DLL. Function return the number of
//stops added from file.
int twoWay::read() 
{
	char temp[31] = "";
	int sID = 0;
	ifstream inFile;

	inFile.open("stoplist.txt");
	if(!inFile)
		return 0;

	//File has been opened
	else
	{
		//search file until "<" has been found 
		//and a matching lineName has been found
		do
		{

			if(inFile.peek() != 62)
				inFile.ignore(100, '\n');

			else
			{
				inFile.ignore(100, '\n');
				inFile.get(temp, 31, '\n');
				inFile.ignore();
			}

		//While a matching line name has not been found, continue
		}while(strcmp(lineName, temp) != 0);

		//This loop will read in stop data once a matching line name has
		//been found. It will continue to read data until the '>' character
		//has been reached
		while(inFile.peek() != 60)
		{
			//add stops to line
			inFile.get(temp, 31, ':');
			inFile.ignore();

			inFile >> sID;
			inFile.ignore(100, '\n');

			if(addStop(temp, sID))
				++num_stops;

		}
		
		inFile.close();
		return num_stops;

	}
	
	inFile.close();
	return 0;
}


//Adds a new stop to the twoWay line. Takes as
//arguments a title for the stop and the ID for the
//stop. Function returns 1 if operation was successful
int twoWay::addStop(char temp[], int sID)
{

	if(!temp)
		return 0;

	else
	{
		//List is empty
		if(!head)
		{	
			head = new stop(temp, sID);
		}

		//Add new stops at head to avoid traversal
		else
		{
			stop *to_add = new stop(temp, sID);
			to_add -> setNext(head);
			head -> setPrevious(to_add);
			head = to_add;
		}

		return 1;
	}
}



//Set the ptr to point to head
//Returns false if ptr is NULL
bool twoWay::start(stop* &ptr)
{
	if(!head)
		return false;

	ptr = head;
	return true;
}


//------------- LOOP CLASS ----------
//A class derived from the LINE class




//Default constructor
loop::loop(): tail(NULL)
{}


//Constructor with an argument for the line name
loop::loop(char n[]): line(n)
{
	tail = NULL;
}



//Copy constructor
loop::loop(loop &to_copy) : line(to_copy)
{
	tail = to_copy.tail;
}



//Destructor that invokes dellocate on tail
//which will go through the CLL and deallocate
//all stop data.
loop::~loop()
{
	deallocate(tail);
}




//Deallocates data recursively from the CLL.
//Upon first invocation the function is given
//the loop's tail pointer.
void loop::deallocate(stop* &ptr)
{
/*	stop *temp = ptr;

	if(ptr -> moveNext(ptr))
	{
		temp -> deallocateStop();
		delete temp;
		temp = NULL;
		deallocate(ptr);
	}

	else
	{*/
		ptr -> deallocateStop();
		delete ptr;
		ptr = NULL;
	//}

}




//Reads in stop data from an external text file, "stoplist.txt".
//Function will read through file until the line name is found. Then
//the function will add stop data to the CLL. Function returns the
//number of stops added to the line.
int loop::read() 
{
	char temp[31] = "";
	int sID = 0;
	ifstream inFile;

	inFile.open("stoplist.txt");
	if(!inFile)
		return 0;

	//File has been opened
	else
	{
		//search file until "<" has been found 
		//and a matching lineName has been found
		do
		{
			if(inFile.peek() != 62)
				inFile.ignore(100, '\n');

			else
			{
				inFile.ignore(100, '\n');
				inFile.get(temp, 31, '\n');
				inFile.ignore();
			}

		}while(strcmp(lineName, temp) != 0);

		//keep adding stop data until the '>' is encountered
		while(inFile.peek() != 60)
		{
			inFile.get(temp, 31, ':');
			inFile.ignore();

			inFile >> sID;
			inFile.ignore(100, '\n');

			//if(addStop(to_add))
			if(addStop(temp, sID))
				++num_stops;

		}

		inFile.close();
		return num_stops; 
	}

	inFile.close();	
	return 0;
} 




//Function to add a stop to the CLL. Takes
//as arguments a name for the stop and an ID for the
//stop. Function returns 1 if operation was successful
int loop::addStop(char temp[], int sID)
{

	//List is empty
	if(!tail)
	{
		tail = new stop(temp, sID);
		tail -> setNext(tail);
	}

	//Enqueue
	else
	{
		stop *to_add = new stop(temp, sID);
		stop *first = tail;
		first -> moveNext(first);
		to_add -> setNext(first);
		tail -> setNext(to_add);
		tail = to_add;
	}

	return 1;
}



//Function that will take a ptr to a stop as
//and arugment and set that ptr to pointer to the 
//loop's first stop in the list. Returns false if 
//tail is NULL.
bool loop::start(stop* &ptr)
{
	if(!tail)
		return 0;

	ptr = tail;

	//tail -> next points to first stop in CLL
	ptr -> moveNext(ptr);
	return true;
}

