#include "FileManager.h"
//loops until a valid file path is entered
void FileManager::setFile() {
	bool noFile = true;
	while (noFile) {
		cout << "Enter File Name: ";
		cin >> fileName;
		inFile.open(fileName);
		if (inFile.is_open()) {
			noFile = false;
		}
	}
}

//returns the name of a validated file path
string FileManager::getName() {
	return fileName;
}