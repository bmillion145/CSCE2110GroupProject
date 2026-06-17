#ifndef CAMPUSMAP_H
#define CAMPUSMAP_H

#include <string>
#include <vector>
using std::string;
using std::vector;//to avoid conflicts

class CampusMap {
    private:
    vector<vector<char>> map;//a vector of a vector of characters
    int row;
    int col;

    public:
    loadFromFile(const string& filename);
};



#endif // CAMPUSMAP_H