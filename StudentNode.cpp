#include "StudentNode.h"
StudentNode::StudentNode(int id, const std::string& name, const std::string& major, float gpa)
    : id(id), name(name), major(major), gpa(gpa), next(nullptr){}