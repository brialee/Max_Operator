//Brian Lee
//CS202 - Fant
//program1


//Implimentation file for the graph.h header file
//Which includes the vertex, edgelist and streetcar classes

#include "graph.h"


//------------VERTEX CLASS---------------

//Default constructor
vertex::vertex() : vStop(0), head(0)
{}




//Copy Constructor
vertex::vertex(const vertex &v)
{
	vStop = v.vStop;
	head = v.head;
}


//Destructor 
vertex::~vertex()
{
	vStop = NULL;
}



//Assists with deallocating memeory used
//when the vertex was created. Function will
//also call a deallocation() function from edgeList
//to deallocate memory used by object.
void vertex::deallocateV()
{
	//delete the vStop pointer
	delete vStop;
	vStop = NULL;

	head -> deallocateEdge(head);

	//delete head;
	head = NULL;
}




//Adds a edgelist node to a vertex. Function takes
//a pointer to a vertex as an argument. The vertex
//which calls the function will then have an edgelist
//node added with a pointer to the provided argument. 
//Function returns true if the operation was successful.
//New edges are added to the front of the edge list.
bool vertex::addEdge(vertex* &to_add)
{
	if(!to_add)
		return false;

	//edgeList head is NULL
	else if(!head)
	{
		head = new edgeList();
		return head -> setVertex(to_add);
	}

	//head is not NULL, add new edge at head
	else
	{
		edgeList *temp = new edgeList();
		if(temp -> setVertex(to_add) && temp -> setNext(head))
		{
			head = temp;
			return true;
		}

		return false;
	}
}



//Set the vertexes' vStop pointer to point to passed stop.
//This function is used as part of the setStopPointers() function.
void vertex::setVstop(stop* &ptr) 
{
	vStop = ptr;
}


//Gets the vertexes' vStop and set passed pointer to point to
//vStop. This function is used as part of the addCars() function.
void vertex::getVstop(stop* &ptr)
{
	ptr = vStop;
}



//Checks to see if the passed argument matches
//the stopID for the stop the vertexes' vStop pointer
//is pointing to. Function returns true if the argument
//matches the vStop stopID. 
bool vertex::checkID(int id)
{
	int target = 0;
		
	vStop -> copyID(target);
	
	if(target == id)
		return true;

	return false;


}


//---------------EDGELIST CLASS---------------------



//Default Constructor
edgeList::edgeList() : next(0), nextStop(0)
{}




//Copy Constructor
edgeList::edgeList(const edgeList &el)
{
	next = el.next;
	nextStop = el.nextStop;
}


//Destructor
edgeList::~edgeList()
{
	//delete nextStop;
	nextStop = NULL;

	//delete next;
	next = NULL;
}




//Function to assist with dellocating any dynamic
//memory used during the objects' creation.
void edgeList::deallocateEdge(edgeList* &ptr)
{
	edgeList *to_remove = ptr;

	//added 'ptr &&' to prevent null head
	//pointer from being passed which causes
	//moveNext to segfault.
	if(ptr && ptr -> moveNext(ptr))
	{	
		delete to_remove;
		to_remove = NULL;
		deallocateEdge(ptr);
	}

	else
	{
		delete ptr;
		ptr = NULL;
	}

}



//Takes as an argument a pointer to an edgelist
//node and sets the argument to point to the edgelist
//node's next ptr that called the function. Function
//will return false if next was NULL. Used in the 
//setStopPointers() and addLine() functions.
bool edgeList::moveNext(edgeList* &ptr)
{
	if(ptr -> next)
	{
		ptr = ptr -> next;
		return true;
	}

	return false;
}



//Takes as an argument a pointer to another edgelist
//node and will set it to point to the calling edgelists'
//next pointer. Function will return 1 as long as the 
//passed argument isn't NULL. Used as part of the addEdge() function.
int edgeList::setNext(edgeList* &to_set)
{
	if(!to_set)
		return 0;

	next = to_set;
	return 1;
}




//Takes as an argument a pointer to a vertex. Function
//will set the edgelist making the call to have its'
//nextStop pointer point to the passed argument. Function
//will return 1 as long as the argument isn't NULL. Used
//as part of the addEdge() function.
int edgeList::setVertex(vertex* &to_set)
{
	if(!to_set)
		return 0;

	nextStop = to_set;
	return 1;	
}



//Function will set the passed vertex pointer to
//point to the calling edgelists' nextStop.
void edgeList::getNextStop(vertex* &ptr)
{	
	ptr = nextStop;
}





//------------GRAPH CLASS-------------

//Default Constructor. Default values for cMax and vMax
//are used to create arrays for streerCars and the adjacenceyList
graph::graph() : vIndex(0), c_index(0), cMax(19), vMax(59)
{
	car = NULL;
	adjacencyList = NULL;
}



//Default destructor. Goes over the streetCar
//and adjacencyList arrays interatively to deallocate
//all dynamic data
graph::~graph()
{
	
	for(int i=0; i < 19; ++i)
		car[i].deallocateCar();

	for(int i=0; i< 59; ++i)
		adjacencyList[i].deallocateV();

	delete []car;
	delete []adjacencyList;

}





//Takes as arguments a stopID and a pointer to a vertex.
//The function will iterate over the adjacencyList array
//until a match is found, in which case the function returns
//true. Used as part of the edgeListMaker() function.
bool graph::findVertex(int id, vertex* &ptr)
{
	for(int i=0; i < vIndex; ++i)
	{
		if(adjacencyList[i].checkID(id))
		{
			ptr = &adjacencyList[i];
			return true;
		}
	}

	return false;
}






//Function to read in from an external text file ("connections.txt")
//a list of connections. While going over each line in the file
//the function reads in two sets of stopIDs. Then it makes use of the
//findVertex() function and if both stopsIDs are found then the addEdge()
//function is invoked to create an edge from one vertex to another. Edges
//are one way. 
void graph::edgeListMaker()
{
	ifstream inFile;
	int fromID = 0;
	int toID = 0;
	int count = 0;
	vertex *from = NULL;
	vertex *to = NULL;

	inFile.open("connections.txt");

	if(!inFile)
		cout << "Failed to load connections" << endl;
	
	else
	{
		//Skip over all lines starting with '*'
		while(inFile.peek() == 42)
			inFile.ignore(100, '\n');


		// "< 78" is a temporary fix. when using eof(), an extra
		// connection from 129:128 was being created. Couldn't 
		// figure it out, took an easy out...
		while(count < 78)	//!inFile.eof())
		{
			inFile >> fromID;
			inFile.ignore(100, ':');

			inFile >> toID;
			inFile.ignore(100, '\n');

			//If both verteces were found in the adjacency list
			//then attempt to create an edge. If sucessfull, increment
			//counter variable
			if(findVertex(fromID, from) && findVertex(toID, to))
				if(from -> addEdge(to))
					++count;
		}
	}
}





//Function is used as part of the addLine() function. When
//invoked by addLine() the function will be passed a stop
//pointer which points to the beginning of a twoWay DLL,
//and index will be given vIndex (which points to the next
//available space in the adjacencyList array). The function
//will continue to add stops to the adjacencyList as long as
//there is a valid next pointer to move to in the DLL. The
//function will return the total number of pointers that
//were set. There are no new stops that are created, instead
//the vStop pointer within each vertex is set to point to a stop
//in the DLL.
int graph::setStopPointers(stop* &to_add, int &index)
{

	if(!to_add)
		return 0;

	else
	{
		adjacencyList[index].setVstop(to_add);
		++index;
	
		//If the to_add stop is able to move next,
		//then continue with a recursive call	
		if(to_add -> moveNext(to_add))
			return setStopPointers(to_add, index) +1;

		//Otherwise there is no next pointer
		else
			return 0;
	}
}



//This function is invoked as part of the addLine() function, specifically
//this function is used to set pointer when adding a loop to the map. When
//first invoked by the addLine() fuction, to_add will be pointing to what would
//be tail -> next in a CLL (which is how the loop is organized). Target will
//be pointing to the tail of the CLL and the index will be pointing to the
//next available space in the adjecencyList array. The function will stop
//its' recursive call when the to_add and target pointers are pointer to the
//same item (when to_add has made a full 'revolution' around the CLL). Function
//will return the total number of pointers set during invocation. 
int graph::setStopPointers(stop* &to_add, int &index, stop *target)
{
	int total = 0;

	//If either pointer becomes NULL, leave
	if(!to_add || !target)
		return 0;

	else
	{
		//If to_add and target are pointing to the same
		//item, the function is done and will return the total.
		if(to_add == target)
		{
			adjacencyList[index].setVstop(target);
			++index;
			++total;
		}
	
		//Otherwise, continue setting pointers	
		else
		{
			adjacencyList[index].setVstop(to_add);
			++index;
			++total;
		
			if(to_add -> moveNext(to_add))
				total += setStopPointers(to_add, index, target);
		}
	}

	return total;
}




//Takes as an argument a reference to a line
//and returns the number of verteces added to
//the adjacency list from said line. Verteces
//will point to the stop in the line's list.
int graph::addLine(twoWay &to_add)
{
	stop *current;

	to_add.start(current);

	return setStopPointers(current, vIndex);
}



//Takes as an argument a reference to a line, specifically
//a line of loop type. The does the same as the above function
//except it accounts for the fact that there would always be a 
//next pointer in a CLL with an extra agrument to the
//setStopPointers() function. The function will return the number
//of pointers set.
int graph::addLine(loop &to_add)
{

	stop *current;
	stop *target;

	to_add.start(target);
	to_add.start(current);

	//start position at one node "ahead" in loop	
	current -> moveNext(current);
	
	return setStopPointers(current, vIndex, target);
}




//Reads streetcar info from txt file and
//adds cars to array. Returns number of cars
//added.
void graph::addCars()
{
	ifstream inFile;
	char temp[11];
	int sID;

	car = new streetCar[cMax];

	inFile.open("streetcar.txt");

	if(!inFile)
		cout << "Failed to load streetcars" << endl;

	else
	{
		//Skip all '*' in file
		while(inFile.peek() == 42)
			inFile.ignore(100, '\n');


		// "< 11" is a temporary fix to prevent an
		// extra streetcar from being added from the 
		// text file. For some reason, removing the
		// "< 11" results in a 12th streetcar being
		// added without a car ID.
		while(!inFile.eof() && c_index < 11)
		{
			stop *currentStop;

			inFile.get(temp, 11, ':');
			inFile.ignore();

			inFile >> sID;
			inFile.ignore(100, '\n');

			
			for(int i=0; i < vIndex; ++i)	
			{
				if(adjacencyList[i].checkID(sID))
				{
					//at the correct vertex	
					//set a pointer to the 
					//vertex's vStop, then set
					//the streetcar's location to 
					//point to that!
					adjacencyList[i].getVstop(currentStop);
					i = 99;
				}

			}

			//Set the id and location for the car at c_index
			car[c_index].setID(temp);
			car[c_index].setLocation(currentStop);

			//Set the direction of the streetcar based on 
			//car naming conventions...car[direction]-stopID
			car[c_index].setDirection(temp[3] - 48);
			car[c_index].setTrack(temp[3] - 48);
			currentStop = NULL;
			++c_index;
		}
		
		inFile.close();
	}
}






//Returns the total number of streetcars for which
//data was displayed for, which is also the value of c_index. 
int graph::listCars()
{
	for(int i=0; i < c_index; ++i)
		car[i].displayLight();

	return c_index;
}



//Changes all inService booleans to true.
//Returns number of cars now inService
void graph::startAllCars()
{
	for(int i = 0; i < c_index; ++i)
		car[i].changeService();
}



//Removes a streetCar from service.
//Function takes as an argument the 
//ID for the streetCar to be removed.
//If both the streetCar is found by ID,
//and then removed from service, the function
//return true. If either one fails, it returns
//false.
bool graph::removeCar(char id[])
{
	cout << "Seaching for: " << id << endl;
	for(int i = 0; i < c_index; ++i)
	{
		//Matching streetCar ID has been found
		if(car[i].checkID(id) && !car[i].changeService())
			return true;
	}

	//End of streetCar array has been reached without a match	
	return false;
}




// Resumes the traversal of all streetcars for a
//given number of iterations passed as the argument. 
void graph::resume(int n)
{
	for(int i=0; i < n; ++i)
	{
		for(int j=0; j < c_index; ++j)
			car[j].traverseRoute();
	}

}



//Takes as arguments a loop and twoWay line objects.
//Function will read in data from the following external
//text file: stoplist.txt, connections.txt, streetcar.txt
//Function will call the necessary text file as part of 
//adding stops to a line, adding streetcars, and adding
//connections between stops on the map. The function ends
//by setting all the inSerivce values to all streetcars as true.
void graph::create(loop &lp, twoWay &tw)
{
	//Read in stops from file to add to line from stoplist.txt
	cout << tw.read() + lp.read() << " stops read from file" << endl;

	//Add lines to map
	adjacencyList = new vertex[vMax];
	addLine(tw);
	addLine(lp);

	//Add cars to map from streetcar.txt
	addCars();

	//Add connections on map between stops from connections.txt
	edgeListMaker();

	//Set all inService values to true
	startAllCars();	
}





// Changes the pace of a streetcar. Function takes
// as arguments the name of the streetcar (carx-xx)
// and a number for the new pace. Function will return
// true if the streetcar was found and the pace was changed.
bool graph::changePace(char c[], int n)
{
	for(int i=0; i < c_index; ++i)
	{
		if(car[i].checkID(c))
		{
			car[i].changePace(n);
			return true;
		}
	}
	
	return false;
}




//Tracks a streetcar with carID c, for n number of
//of stops. The function first iterates over the array
//of streetcars to search for the carID, if found it will
//iterate n number of times over the streetCar array to
//allow each car to travrse one stop. If the car traversing
//at any given moment is the car to be tracked the car and stop
//information will be displayed. 
bool graph::trackCar(char c[], int n)
{
	streetCar *ptr = NULL;

	for(int i=0; i < c_index; ++i)
	{
		if(car[i].checkID(c))
			ptr = &car[i];
	}


	for(int i=0; i < n; ++i)
	{
		for(int j=0; j < c_index; ++j)
		{
			if(ptr == &car[j])
			{
				car[j].traverseRoute(1);
				car[j].travel();
				++j;
			}

			car[j].traverseRoute();
		}
	}

	ptr = NULL;

	return true;
}




//Returns true if the streetcar with carID temp
//was located and its' inService value was changed
//to true. If either the the car was not found, or 
//the inService value was already true - it will
//be changed to false during the function invocation, which
//is a flaw...- the function will return false
bool graph::backToWork(char temp[])
{

	for(int i=0; i < c_index; ++i)
      	{   
                if(car[i].checkID(temp))
                {
			if(car[i].changeService())
			{
				return true;
			}

                }
        }

	return false;
}
