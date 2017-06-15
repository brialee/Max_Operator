//header file for the graph class

#include "line.h"

//An edgelist has a vertex as well as a pointer to another edgelist
class edgeList
{
	public:
		edgeList(); //default constructor
		edgeList(const edgeList &);	//copy constructor
		~edgeList();//destructor

		//Recursively dealloates data in the edgeList
		//INPUT: edgeList pointer
		//POSTCON: edgeList pointer is set to NULL
		void deallocateEdge(edgeList* &);

		//Sets next pointer
		//INPUT: pointer to edgeList to be connected
		//POSTCON: next will point to passed argument
		//OUTPUT: 1 if successful
		int setNext(edgeList* &);


		//Sets nextStop pointer
		//INPUT: pointer to a vertex
		//POSTCON: nextStop points to passed argument
		//OUTPUT: 1 if succesful
		int setVertex(class vertex* &);

		//Move argument to argument -> next
		//INPUT: EdgeList pointer
		//POSTCON: argument is now pointer to argument -> next
		//OUTPUT: false if unable to traverse
		bool moveNext(edgeList* &);


		//Sets a pointer to nextStop
		//INPUT: vertex pointer
		//OUTPUT: NULL is nextStop is NULL
		//POSTCON: argument now points to nextStop
		void getNextStop(vertex* &);

	protected:
		edgeList *next;	//pointer to 'next' edgeList node
		class vertex *nextStop;//pointer to vertex
		

};




//A vertex has a stop and an edgelist pointer
class vertex
{
	public:
		vertex();	//constructor
		vertex(const vertex &);	//copy constructor
		~vertex();	//destructor

		//Sets vStop to null and calls similar function for edgelist
		//POSTCON: vStop and head are dellocated of memory
		void deallocateV();

		//Sets vStop to point to argument
		//POSTCON: vStop now points to passed argument
		void setVstop(stop* &);


		//Sets pointer to point to vStop
		//POSTCON: argument now points to vStop
		void getVstop(stop* &);


		//Checks to see if argument matches vStop -> stopID
		//INPUT: int for stopID
		//OUTPUT: returns true if vStop -> carID matches argument
		bool checkID(int );


		//Adds edge to head with passed argument as edge's nextStop
		//INPUT: pointer to a vertex
		//OUTPUT: true if operation was successful
		//POSTCON: vertex now has an edge that points to passed argument
		bool addEdge(vertex* &);


		//Apparently this function is nowhere to be found, yet uncommenting
		//the function and compiling causes no issues.....	
		//int nextStop(vertex* &);


	protected:
		stop *vStop; //pointer to a stop
		edgeList *head;//head pointer to edgeList

};




//A grap has an array of verteces (adjacencyList) and an array
//of streetCars
class graph
{
	public:
		graph();	//Constructor
		~graph();	//Destructor

		//Adds a twoWay to the graph
		//INPUT: a twoWay line object
		//OUTPUT: total number of stops added from passed line
		//POSTCON: a vertex in the adjancecyList will have a vStop pointer
		//which points to a stop in the twoWay line
		int addLine(twoWay &);


		//Add a Loop to the graph
		//INPUT: a loop line object
		//OUTPUT: total number of stops added from passed line
		//POSTCON: a vertex in the adjacencyList will have a vStop
		//pointer that points to a stop in the loop Line.
		int addLine(loop &);

		//Beings the process of adding passed line
		//to the graph. Also calls the addLine(), addCars()
		//and edgeListMaker() functions.
		//INPUT: loop and twoWay objecst
		//POSTCON: car and adjacencyList arrays have pointers set
		//to data based on passed lines and external files
		void create(loop&, twoWay&);

		//Adds cars to car array from external text file "streetcar.txt"
		//POSTCON:car array will have cars added from file
		void addCars();

		//Displays a list of all cars on the track
		//OUTPUT: list of cars on map, and number of cars displayed
		int listCars();


		//Sets all cars to have true inService values
		//POSTCON: all cars in car[] have inService set to true
		void startAllCars();


		//Read in data from external file "connections.txt"
		//POSTCON: each vertex in adjacencyList[] will have a edgelist created
		void edgeListMaker();


		//Tracks a streetCar as it moves
		//OUTPUT: Displays current stops as car moves along a line
		//INPUT: carID and number of stops to track car for
		bool trackCar(char [], int);


		//Change the pace of a car
		//INPUT: carID and new pace
		//OUTPUT: true if car was found and pace changed
		//POSTCON: car matching carID has new pace
		bool changePace(char [], int);


//		int startCar(streetCar &, stop &);


		//Removes a car from service
		//INPUT: carID
		//OUTPUT: Returns true if car was found and inService changed to false
		//POSTCON: carID will no longer be in service is successful
		bool removeCar(char []);


		//Places a streetcar back into service
		//INPUT: carID
		//OUTPUT: returns true if car was found and is now in service
		//POSTCON: if successful, car will now be in service
		bool backToWork(char []);


		//Allows the streetcars to resume traversal on track
		//INPUT: number of stops each streetcar is allowed to traverse
		//POSTCON: each car in car[] will have traversed passed number of stops
		void resume(int);

	protected:
		vertex *adjacencyList; //array to verteces
		streetCar *car; //array for streetCars

		//Function to set pointers in a twoWay line, used as part of edgeListMaker()
		//INPUT: a stop and a index in the adjacencyList[] that the stop is associated with
		//OUTPUT: 1 if successful
		int setStopPointers(stop* &, int &);

		//Function to set pionters in a loop, used as part of edgeListMaker()
		//INPUT: a stop pointer, an int for car[] index, and a pointer to the tail of the loop
		int setStopPointers(stop* &, int &, stop *);


		//Finds a vertex in the adjacencyList[]
		//INPUT: a stop ID and a pointer to a vertex
		//POSTCON: passed vertex will point to vertex having a stop with matching stopID
		//OUTPUT: true if matching vertex was found
		bool findVertex(int, vertex* &);

		int vIndex, c_index, cMax, vMax; //variables to keep track of how many items are in array, and array max

};
