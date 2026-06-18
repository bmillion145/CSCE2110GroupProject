Group Member Names:
  Benett Miller
  Andrew Saul - worked on CampusMap.h, CampusMap.cpp, FileManager.h and FileManager.cpp 
Compliation Instructions:

Execution Instructions:

Description of Implemented Features:
  - StudentNode.cpp and StudentNode.h:
      The h file declares the nodes, classes, and functions that are defined in the cpp file. The
      cpp file has a destructor, copy constructor, copy assignment operator, move constructor
      and move assignment operator for linked list manipulation. Other functions for use on the menu
      are insert at the end of the list, remove student by id, remove student by name, (those two use
      type overloading,) search for student by id, search for student by name, (also use type overloading,)
      update students grade by id, print all students, file verification, loading students by file,
      save students by file, as well as helper functions to return the number of students in the list,
      clear the list, and checking if the list is empty.   
  - CampusMap.h and CampusMap.cpp:
      delcares and defines a class with functions allowing for the user to input a map file that is then read and stored.
      This stored map can then be used by calling the functions printMap or the user can find information
      about their location by calling the findMe function that will display the current area they are in
      and all adjacent areas.
    -FileManager.cpp FileManager.h:
      declares and defines a class with funcations that allow for the program to take a user submited file name and
      verify if it is a vlaid file path then storing the name for later use.
