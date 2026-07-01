#include "CampusMap.h"

//reads the map file and adds it to a dynamic 2d array
void CampMap::readMapFile() {
	//calling File managers setfile function to get and validate file
	readFile.setFile();
	//sets in file stream
	rFile.open(readFile.getName());
	//takes in the number of rows and columns from the in file
	rFile >> numOfRow >> numOfCol;
	//sets the array to a size based on the specified rows and columns
	gridMap = new char* [numOfRow];
	for (int i = 0; i < numOfRow; ++i) {
		gridMap[i] = new char[numOfCol];
	}
	for (int i = 0; i < numOfRow; ++i) {
		for (int j = 0; j < numOfCol; ++j) {
			rFile >> gridMap[i][j];
		}

	}
}

//takes user coordinates and tells them the ID of the current and adjacent locations 
void CampMap::findMe() {
	if (mapFlag) {
		int x = 0, y = 0;
		bool blocked = true;
		//taking input for user coordinates
		while (blocked) {
			cout << "Enter X and Y coordinates respectively: ";
			cin >> x >> y;
			// checking to make sure a valid set was entered
			if (deCode(x, y) == "Blocked") {
				cout << "Area entered is marked as blocked, please enter a valid coordinate set\n";
			}
			else if (deCode(x, y) == "Unknown" || deCode(x, y) == "Off Map") {
				cout << "Area is invalid or off the designated map grid, please enter a valid coordinate set\n";
			}
			else {
				blocked = false;
			}

		}


		//sends the chords to deCode to get the names of location specified by the characters in 2d array
		cout << "Location: " << deCode(x, y) << endl;
		cout << "Up: " << deCode(x, y - 1) << endl;
		cout << "Down: " << deCode(x, y + 1) << endl;
		cout << "Left: " << deCode(x - 1, y) << endl;
		cout << "Right: " << deCode(x + 1, y) << endl;
	}
	else {
		cout << "No map file loaded please load a map\n";
	}
}

//decodes the map characters into their respective tile types
	string CampMap::deCode(int x, int y) {
		char toDeCode;
		//checks to makes sure value is inside of the map stops out of range errors
		if (x < 0 || x >= numOfCol || y < 0 || y >= numOfRow) {
			return "Off Map";
		}
		//takes the x y and sorts uses a switch case to return the proper text relating the the character
		toDeCode = gridMap[y][x];
		switch (toDeCode) {
		case 'R':
			return "Road";
			break;
		case 'B':
			return "Building";
			break;
		case 'C':
			return "Classroom";
			break;
		case 'L':
			return "Library";
			break;
		case 'P':
			return "Parking Lot";
			break;
		case 'X':
			return "Blocked Area";
			break;
		default:
			return "unknown";
		}
		//here for extra error handling just in case
		return "Unknown";
	}


//deleted the dynamically allocated array
CampMap::~CampMap() {
	for (int i = 0; i < numOfRow; ++i) {
		delete[] gridMap[i];
		delete[] gridMap;

	}
}

//prints out the map
void CampMap::printMap() {
	if (mapFlag) {
		//sets the top column number indicators
		cout << "  ";
		for (int i = 0; i < numOfCol; ++i) {
			cout << i;
		}
		cout << endl;
		//prints the map
		for (int i = 0; i < numOfRow; ++i) {
			//prints out the row number indicators 
			cout << i << " ";
			for (int j = 0; j < numOfCol; ++j) {
				cout << gridMap[i][j];
			}
			cout << endl;
		}
	}
	else {
		cout << "No map file loaded, please load a map\n";
	}

}

void CampMap::mapStats() {
	if (mapFlag) {
		int numB = 0, numC = 0, numL = 0;

		for (int i = 0; i < numOfRow; ++i) {
			for (int j = 0; j < numOfCol; ++j) {
				if (gridMap[i][j] == 'B') {
					++numB;
				}
				else if (gridMap[i][j] == 'C') {
					++numC;
				}
				else if (gridMap[i][j] == 'L') {
					++numL;
				};
			}
		}
		cout << "Number of buildings: " << numB << " Number of classrooms: " << numC << " number of libraries: " << numL << endl;
	}
	else {
		cout << "No map file loaded please load a map\n";
	}
}
