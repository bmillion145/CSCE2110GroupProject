#include "StudentNode.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>


using namespace std;

//  Destructor
StudentList::~StudentList() {
    clear();
}

// Copy Constructor
StudentList::StudentList(const StudentList& other) : head(nullptr) {
    StudentNode* current = other.head;
    while (current != nullptr) {
        insert(current->id, current->name, current->major, current->grade);
        current = current->next;
    }
}

// Assignment Operator
StudentList& StudentList::operator=(StudentList&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    clear();                   
    head = other.head;           
    other.head = nullptr;
    return *this;
}

// Move Constructor
StudentList::StudentList(StudentList&& other) noexcept : head(other.head) {
    other.head = nullptr;
}

// Move Assignment Operator
StudentList& StudentList::operator=(StudentList&& other) noexcept {
    if (this != &other) {
        clear();
        head = other.head;
        other.head = nullptr;
    }
    return *this;
}

// Insert student at the end of the list
void StudentList::insert(int id, const string& name, const string& major, double grade) {
    StudentNode* node = new StudentNode(id, name, major, grade);
    if (head == nullptr) {
        head = node;
        return;
    } 
    StudentNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = node;
}

// Remove student by ID (removes the first occurrence)
void StudentList::remove(int id) {
    StudentNode* current = head;
    StudentNode* previous = nullptr;
    while (current != nullptr) {
        if (current->id == id) {
            if (previous == nullptr) {
                head = current->next; 
            } else {
                previous->next = current->next; 
            }
            delete current; 
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Remove student by name (removes the first occurrence)
void StudentList::remove(const string& name) {
    StudentNode* current = head;
    StudentNode* previous = nullptr;
    while (current != nullptr) {
        if (current->name == name) {
            if (previous == nullptr) {
                head = current->next; 
            } else {
                previous->next = current->next; 
            }
            delete current; 
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Search for a student by ID (non-const and const version)
StudentNode* StudentList::search(int id) {
    StudentNode* current = head;
    while (current != nullptr) {
        if (current->id == id) {
            return current; 
        }
        current = current->next;
    }
    return nullptr; 
}

StudentNode* StudentList::search(int id) const {
    StudentNode* current = head;
    while (current != nullptr) {
        if (current->id == id) {
            return current; 
        }
        current = current->next;
    }
    return nullptr; 
}

// Search for a student by name (non-const and const version)
StudentNode* StudentList::search(const string& name)  {
    StudentNode* current = head;
    while (current != nullptr) {
        if (current->name == name) {
            return current; 
        }
        current = current->next;
    }
    return nullptr; 
}

const StudentNode* StudentList::search(const string& name) const {
    StudentNode* current = head;
    while (current != nullptr) {
        if (current->name == name) {
            return current; 
        }
        current = current->next;
    }
    return nullptr; 
}

// Update a student's grade by ID
void StudentList::updateGrade(int id, double newGrade) {
    StudentNode* node = search(id);
    if (node != nullptr) {
        node->grade = newGrade;
    }
}

// Print all students 
void StudentList::printList() const {
    if (head == nullptr) {
        cout << "(list is empty)\n";
        return;
    }
    StudentNode* cur = head;
    while (cur != nullptr) {
        cout << "ID: " << cur->id
             << " | Name: " << cur->name
             << " | Major: " << cur->major
             << " | Grade: " << fixed << setprecision(2) << cur->grade << "\n";
        cur = cur->next;
    }
}

// load students from a file
bool StudentList::loadFromFile(const string& filename) {
    ifstream in(filename);
    if (!in) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }
    clear();
    
    // Read each line and parse student data
    int id;
    string name, major;
    double grade;
    while (in >> id >> name >> major >> grade) {
        insert(id, name, major, grade);
    }
    return true;
}

// save students to a file
bool StudentList::saveToFile(const string& filename) const {
    ofstream out(filename);
    if (!out) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }
    StudentNode* current = head;
    while (current != nullptr) {
        out << current->id << " " 
            << current->name << " " 
            << current->major << " " 
            << fixed << setprecision(2) << current->grade << "\n";
        current = current->next;
    }
    return true;
}

// helper functions
// Return the number of students in the list
int StudentList::size() const {
    int count = 0;
    StudentNode* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// Clear the list and free memory
void StudentList::clear() {
    StudentNode* current = head;
    while (current != nullptr) {
        StudentNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

// Check if the list is empty
bool StudentList::isEmpty() const {
    return head == nullptr;
}