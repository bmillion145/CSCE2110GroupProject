#include "FileManager.h"
class CampMap {
public:
	//reads the map file and adds it to a dynamic 2d array
	void readMapFile();
	//takes user chordinates and tells them the ID of the current and adjacent locations 
	void findMe();
	//decodes the map characters into their repective tile types
	string deCode(int x, int y);
	//returns the number of buildings libraries and clasrooms
	void mapStats();
	//deleted the dynamicly allocated array
	~CampMap();
	//prints out the map
	void printMap();


private:
	bool mapFlag = false;
	int numOfRow = 0, numOfCol = 0;
	//2d array 
	char** gridMap;
	//in file and file system 
	ifstream rFile;
	FileManager readFile;
};
