#ifndef STUDENTNODE_H
#define STUDENTNODE_H
#include <string>
using std::string;//using namespace std is not recommended in header files to avoid name conflicts

struct StudentNode {
    int id;
    string name;
    string major;
    float gpa;
    StudentNode* next;
    // Constructor to initialize a student node
    StudentNode(int, const string, const string, float);
};



#endif // STUDENTNODE_H