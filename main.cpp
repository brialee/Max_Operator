//Brian Lee
//CS202 - Fant
//Program 1


//Main.cpp File


#include "graph.h"
#include <cstdlib>

//Prototypes
void explanation();	//brief explanation of the program
void displayMenu();	//displays a menu with choices



int main()
{
	char oline[31] = "Orange Line";
	char bline[31] = "Blue Line";
	char temp[11];
	bool exit = false;
	int selection;

	graph map;
	loop orange(oline);	//create a loop with passed name
	twoWay blue(bline);	//create a twoWay line with passed name
	map.create(orange, blue);	//add the two lines to the map

	explanation();
	do
	{
		displayMenu();
		cout << "Enter Selection: ";
		cin >> selection;
		cin.ignore(100, '\n');

		//Track a Car
		if(selection == 1)
		{
			int n;

			cout << "How many stops would you like to track a streetcar for?" << endl;
			cout << "Enter number: ";
			cin >> n;
			cin.ignore(100, '\n');

			cout << "Enter streetcar name in format 'carX-XX'" << endl;
			cout << "Enter name: ";
			cin.get(temp, 11, '\n');
			
			if(map.trackCar(temp, n))
				cout << "\n\n.....Tracking Complete" << endl;

			else
				cout << "Unable to locate streetcar for tracking" << endl;
		}
	
		//Take a car out of serivce
		else if(selection == 2)
		{
			cout << "Provide the name of the streetcar you want removed, ex. carX-XX" << endl;
			cout << "Name: ";
			cin.get(temp, 11, '\n');
			cin.ignore(100, '\n');
		
			if(map.removeCar(temp))
				cout << "Streetcar " << temp << " has been taken out of service." << endl;

			else
				cout << "Unable to alter streetcar..." << endl;

		}
		
		//Add a car to a line	< -- -- -- -- CURRENT DOESN'T WORK
		else if(selection == 3)
			cout << "3 under construction" << endl;


		//Change the pace of a car	
		else if(selection == 4)
		{
			int n;

			cout << "Provide the name of the streetcar, ex. carX-XX" << endl;
			cout << "Name: ";
			cin.get(temp, 11, '\n');

			cout << "Enter the new pacing: ";
			cin >> n;
			cin.ignore(100, '\n');

			if(map.changePace(temp, n))
				cout << "Pace was successfully change for " << temp << endl;

			else
				cout << "Pace change failed..." << endl;

		}


		//Locate all cars	
		else if(selection == 5)
			cout << map.listCars() << " total streetcars on the map." << endl;


		//Place an existing streetcar back in service
		else if(selection == 6)
		{
			cout << "Enter streetcar name, ex. carX-XX" << endl;
			cout << "Enter name: ";
			cin.get(temp, 11, '\n');
			cin.ignore(100, '\n');

			if(map.backToWork(temp))
				cout << "Streetcar " << temp << " is now in service." << endl;

			else
				cout << "Unable to make changes....." << endl;
		}


		//Exit	
		else if(selection == 7)
		{
			cout << "Good Bye" << endl;
			exit = true;
		}

		else
			cout << "Invalid Seleciton" << endl;

		//get random number between 1-10
		//and have each car make x num traversals
		if(!exit)
		{
			srand(time(NULL));
			map.resume((rand() % 10) + 1);
		}


	}while(!exit);

	
	cout << "\n\n\nEnd of program" << endl;
	return 0;
}




//Function Bodies


//Displays a menu of options for the user to select
void displayMenu()
{
	cout << "\n\nChoose from an option below:" << endl;
	cout << "1 - Track a streetcar" << endl;
	cout << "2 - Take a streetcar out of service" << endl;
	cout << "3 - Add a new streetcar to a line" << endl;
	cout << "4 - Change the pace of a streetcar" << endl;
	cout << "5 - Locate all streetcars" << endl;
	cout << "6 - Put an existing streetcar back in service" << endl;
	cout << "7 - Exit" << endl;
	cout << "--------------------------------------" << endl;
}



//Displays an explanation of the program
void explanation()
{
	cout << "\n\n\t\tWelcome Streetcar Architect....." << endl;
	cout << "Below you will be presented with a menu of options to choose from." << endl;
	cout << "After selecting an option, the program will carry out your request and" << endl;
	cout << "then pause for a certain amount of time to allow the streetcars to move \nto their next stop and drop off passengers.";
	cout << " After that, the menu of options will be \navailable again. The time it takes for";
	cout << " the streetcars to finish is anywhere from 1-10 seconds.\n\n";

}
