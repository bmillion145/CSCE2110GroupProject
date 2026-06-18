#include "CampusMap.h"

//reads the map file and adds it to a dynamic 2d array
void CampMap::readMapFile() {
	//calling File managers setfile function to get and validate file
	readFile.setFile();
	//sets in file stream
	rFile.open(readFile.getName());
	//takes in the number of rows and collems from the in file
	rFile >> numOfRow >> numOfCol;
	//sets the array to a size based on the specified rows and collems
	gridMap = new char* [numOfRow];
	for (int i = 0; i < numOfRow; ++i) {
		gridMap[i] = new char[numOfCol];
	}
	for (int i = 0; i < numOfRow; ++i) {
		for (int j = 0; j < numOfCol; ++j) {
			rFile >> gridMap[j][i];
		}

	}

}
	//takes user chordinates and tells them the ID of the current and adjacent locations 
void CampMap::findMe() {
	int x = 0, y = 0;
	bool blocked = true;
	//taking input for user chordinates
	while (blocked){
		cout << "Ender X and Y chordinate respectivly: ";
		cin >> x >> y;
	// checking to make sure a valid set was entered
		if(deCode(x,y) == "Blocked"){
				cout << "Area entered is marked as blocked please enter a valid chordiante set\n";
			}else if (deCode(x,y) == "Unkown" || deCode(x,y) == "Off Map"){
				cout << "Area is invalid or off the designated map grid please enter a valid chordinate set"
			}else {
				blocked = false;
			}

		}

}
	//sends the chords to deCode to get the names of location specified by the characters in 2d array
	cout << "Location: " << deCode(x, y) <<endl;
	cout << "Up: " << deCode(x , y -1) <<endl;
	cout << "Down: " << deCode(x, y + 1) << endl;
	cout << "Left: " << deCode(x - 1, y) << endl;
	cout << "Right: " << deCode(x + 1, y) << endl;
}
	//decodes the map characters into their repective tile types
string CampMap::deCode(int x, int y) {
	char toDeCode;
	//checks to makes sure value is inside of the map stops out of range errors
	if (x < 0 || x > numOfRow || y < 0 || y > numOfCol) {
		return "Off Map";
	}
	//takes the x y and sorts uses a switch case to return the proper text relating the the character
	toDeCode = gridMap[x][y];
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
		return "unkown";
	}
	//here for extra error hanling just in case
	return "Unkown";
}

//deleted the dynamicly allocated array
CampMap::~CampMap() {
	for (int i = 0; i < numOfRow; ++i) {
		delete[] gridMap[i];
		delete[] gridMap;

	}
}
//prints out the map
void CampMap::printMap() {
	//sets the top collem number indicators
	cout << "  ";
	for (int i = 0; i < numOfRow; ++i) {
		cout << i;
	}
	cout << endl;
	//prints the map
	for (int i = 0; i < numOfRow; ++i) {
		//prints out the row number indicators 
		cout << i << " ";
		for (int j = 0; j < numOfCol; ++j) {
			cout << gridMap[j][i];
		}
		cout << endl;
	}


}

