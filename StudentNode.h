#ifndef STUDENTNODE_H
#define STUDENTNODE_H

#include "FileManager.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using namespace std;


// Node structure for a linked list of students
struct StudentNode {
    int id;
    string name;
    string major;
    double grade;
    StudentNode* next;

    StudentNode(int i, const string& n, const string& m, double g)
        : id(i), name(n), major(m), grade(g), next(nullptr) {}

    string getLine() const {
        ostringstream oss;
        oss << id << " " << name << " " << major << " " << fixed << setprecision(2) << grade;
        return oss.str();
    }
};

// Linked List class to manage StudentNodes
class StudentList {
private:
    StudentNode* head;

public:
    // Constructor
    StudentList() : head(nullptr) {};

    // Destructor
    ~StudentList(); 

    // Copy Constructor
    StudentList(const StudentList& other);

    // Assignment Operator
    StudentList& operator=(const StudentList& other);

    // Move Constructor
    StudentList(StudentList&& other) noexcept;

    // Move Assignment Operator
    StudentList& operator=(StudentList&& other) noexcept;

    // Insert student at the end of the list
    void insert(int id, const string& name, const string& major, double grade);

    // Remove student by ID
    void remove(int id); 

    // Remove student by name
    void remove(const string& name);

    // Search for a student by ID (with overloading for const correctness)
    StudentNode*       search(int id);
    const StudentNode* search(int id) const;

    // Search for a student by name (with overloading for const correctness)
    StudentNode*       search(const string& name);
    const StudentNode* search(const string& name) const;

    // Update a student's grade by ID
    void updateGrade(int id, double newGrade);

    // Print all students in the list
    void printList() const; 

    // Prints average grade of all students in the list
    void averageGrade() const;

    // File I/O operations
    bool loadFromFile();
    bool saveToFile(const string& filename = "students.txt") const;

    // Helper functions
    int size() const;
    void clear();
    bool isEmpty() const;

    ifstream rFile;
    FileManager readFile;


};


#endif

