Max Operator Program


This program was made for CS201 at PSU with the purpose of demonstrating
OOP principles and design. This was the first assignment of the class for
Winter 2016. Program assumes that correct user input is provided. Tested
and compiled for Ubuntu Linux environment. 


Abstract:
Create an object oriented program that will create a scheduling service
for a public transit streetcar system. This program should allow allow
for a controller to see where all the cars are located, add cars to
a track, and remove a car from service.

Data Structures:
A graph is used to handle the collection of tracks and the list of stops
as an adjacency list. Tracks that are loops should be implemented as a
circular linked list, and two way tracks as doubly linked lists. Data for
the program should come from an external text file.


Using the Program:
Run the 'make' command, then "./maxOperator" and follow the program prompts.
Once finished, run "make clean" to remove the object files and executable. 

Known Issues:
Besides providing incorrect user input, if a streetcar is removed and
then the user attempts to track it, it will not display a message that
the streetcar cannot be found, instead it will track a "blank" car.
