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
    StudentNode(int id, const string& name, const string& major, float gpa) : 
    id(id), name(name), major(major), gpa(gpa), next(nullptr) {}
};



#endif // STUDENTNODE_H