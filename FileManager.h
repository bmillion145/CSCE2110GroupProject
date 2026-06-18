
#ifndef File_Manager
#define File_Manager

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//handles the retrival and validation of in files
class FileManager {
public:
	//sets the file instream through taking a file name from user input
	void setFile();
	//returns the file name of a validated file
	string getName();

private:
	ifstream inFile;
	string fileName;
};
#endif
