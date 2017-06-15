//Brian Lee
//CS202 - Fant
//Program1


//Header file for a line class. Also included are 
//two types of lines, a loop and a bi-directional line.
//These two types are just specialzed versions of a line.
//Loops are implimented as CLL, while a bi-directional line
//is implimented as a DLL.

#include "node.h"
#include <fstream>

class line 
{
	public:
		line();	//default constructor
		line(char []);	//constructor with argument
		line(line &to_copy);	//copy constructor
		~line();	//destructor
		void display();	//displays all protected data

	protected:
		int max_cars; //max number of cars allowed on line, set to 8 by default
		int num_cars; //number of cars on the line
		int num_stops;//number of stops on a line
		char *lineName;//variable for the line name
};


class twoWay : public line
{
	public:
		twoWay();	//default constructor
		twoWay(char []);	//constructor with argument
		twoWay(twoWay &to_copy);	//copy constructor
		~twoWay();	//destructor

		//Deallocates all stop data the line by recursion.
		//INPUT: pointer to a stop, called with head on 1st invocation
		//POSTCON: all data for stops on a line is deallocated
		void deallocate(stop* &);


		//Read in stop data from external file "stoplist.txt"
		//OUTPUT: total number of stops added to line from file
		//POSTCON: head will point to beginning of DLL popualated with stops
		int read();

		//Add an individual stop to a line
		//INPUT: name and ID for a stop
		//OUTPUT: 1 if stop was added
		int addStop(char [], int);


		//Sets ptr argument to point to head
		//INPUT: stop pointer
		//POSTCON: argument now points to start of DLL
		//OUTPUT: returns true if head isn't NULL
		bool start(stop* &ptr);

	protected:
		stop *head;	//head pointer for DLL
};





class loop: public line
{
	public:
		loop();	//default constructor
		loop(char []);	//constructor with argument
		loop(loop &to_copy); //copy constructor
		~loop();	//destructor

		//Recursively deallocates all stop data from CLL
		//INPUT: stop pointer, at first invocation argument is tail
		//POSTCON: all stop data is dellocated in CLL
		void deallocate(stop* &);

		//Reads in stop data from external file "stoplist.txt"
		//OUTPUT: number of stops read from file
		//POSTCON: tail points to CLL of stops
		int read();

		//Adds a stop to a line
		//OUTPUT: returns 1 if operations was succesful
		//INPUT: line name and ID
		int addStop(char [], int);


		//Sets argument to point to first stop in CLL (tail -> next)
		//OUTPUT: returns true is tail was not NULL
		//INPUT: pointer to a stop
		bool start(stop* &ptr);

	protected:
		stop *tail;	//tail pointer for CLL		
};
