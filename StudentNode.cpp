#include "StudentNode.h"

StudentNode::StudentNode(int id, const string& name, const string& major, float gpa) 
    : id(id), name(name), major(major), gpa(gpa), next(nullptr) {}