#ifndef STUDENTNODE_H
#define STUDENTNODE_H

#include <iostream>
#include <string>
#include <fstream>

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
        return to_string(id) + " " + name + " " + major + " " + to_string(grade);
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

    // Move Assignment Operator (commented out for now)
    // StudentList& operator=(StudentList&& other) noexcept;

    // Insert student at the end of the list
    void insert(int id, const string& name, const string& major, double grade);

    // Remove student by ID
    void remove(int id); 

    // Remove student by name
    void remove(const string& name);

    // Search for a student by ID (with overloading for const correctness)
    StudentNode* search(int id);
    StudentNode* search(int id) const;

    // Search for a student by name (with overloading for const correctness)
    StudentNode*       search(const string& name);
    const StudentNode* search(const string& name) const;

    // Update a student's grade by ID
    void updateGrade(int id, double newGrade);

    // Print all students in the list
    void printList() const; 

    // File I/O operations
    bool loadFromFile(const string& filename = "students.txt");
    bool saveToFile(const string& filename = "students.txt") const;

    // Helper functions
    int size() const;
    void clear();
    bool isEmpty() const;


};
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

