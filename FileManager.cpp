#include "CampusMap.h"
#include "FileManager.h"
#include <iostream>
using std::cout;
using std::endl;

bool CampusMap::loadFromFile(const string& filename) {
    FileManager fm;
    return fm.loadMap(filename, map, rows, cols);
}
