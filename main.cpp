#include <iostream>
#include <fstream>
#include "CampusMap.h"
#include "QueueSystem.h"
#include "StudentNode.h"
using namespace std;

void campusMapMenu(CampMap& campusMap);
void studentManagementMenu(StudentList& studentList);
void advisingQueueMenu(AdvisingQueue& advisingQueue);
void campusStatisticsMenu(StudentList& studentList, CampMap& campusMap, AdvisingQueue& advisingQueue);

int main(){
     CampMap campusMap;
     StudentList studentList;
     AdvisingQueue advisingQueue;
     int choice;

    do
    {
        cout << "\n========================================\n";
        cout << " Campus Exploration System\n";
        cout << "========================================\n";
        cout << "1. Campus Map\n";
        cout << "2. Student Management\n";
        cout << "3. Advising Queue\n";
        cout << "4. Campus Statistics\n";
        cout << "5. Exit\n";
        cout << "\nEnter Choice: ";

        cin >> choice;
                switch(choice)
        {

            case 1:
                campusMapMenu(campusMap);
                break;

            case 2:
                studentManagementMenu(studentList);
                break;

            case 3:
                advisingQueueMenu(advisingQueue);
                break;

            case 4:
                campusStatisticsMenu(studentList, campusMap, advisingQueue);
                break;

            case 5:
                cout << "\nExiting Program...\n";
                break;

            default:
                cout << "\nInvalid Choice. Try Again.\n";
        }
    } while (choice != 5);

    return 0;
}

//submenus for each of the main menu options
void campusMapMenu(CampMap& campusMap)
{
    do {
        cout << "\nCampus Map Menu\n";
        cout << "1. Load Map\n";
        cout << "2. Find Location\n";
        cout << "3. Print Map\n";
        cout << "4. Return to Main Menu\n";
        cout << "\nEnter Choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                // campusMap.loadMap();
                    campusMap.readMapFile();
                    cout << "Map loaded successfully.\n";
                break;

            case 2:
                campusMap.findMe();
                break;

            case 3:
                // campusMap.printMap();
                campusMap.printMap();
                break;

            case 4:
                return;

            default:
                cout << "\nInvalid Choice. Try Again.\n";
        }
    } while (true);
}


void studentManagementMenu(StudentList& studentList){
   do{ 
        cout << "\nStudent Management Menu\n";
        cout << "----------------------------------------\n";
        cout<<"1. Load students from file\n";
        cout << "2. Add Student\n";
        cout << "3. Remove Student\n";
        cout << "4. Search Student\n";
        cout << "5. Update Grade\n";
        cout << "6. Print All Students\n";
        cout << "7. Return to Main Menu\n";
        cout << "\nEnter Choice: ";

        int input;
        cin >> input;

       switch (input) {

    case 1:
        studentList.loadFromFile();
            
    case 2:{
        //adding student
        int id;
        string name, major;
        double grade;

        cout << "Enter ID: ";
        cin >> id;

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Major: ";
        getline(cin, major);

        cout << "Enter Grade: ";
        cin >> grade;

        studentList.insert(id, name, major, grade);
        break;
    }

    case 3:{
        // removing student by ID
        int removeId;
        cout << "Enter ID of student to remove: ";
        cin >> removeId;
        studentList.remove(removeId);
        cout << "Student removed.\n";
        break;
    }

    case 4:{
        // searching for student by ID
        int searchId;
        cout << "Enter ID of student to search: ";
        cin >> searchId;
        StudentNode* found = studentList.search(searchId);
        if (found) {
            cout << "Student Found: ID: " << found->id
                 << " | Name: " << found->name
                 << " | Major: " << found->major
                 << " | Grade: " << found->grade << "\n";
        } else {
            cout << "Student not found.\n";
        }
        break;
    }   

    case 5:{
        //updates grades
        int updateId;
        double newGrade;
        cout << "Enter ID of student to update grade: ";
        cin >> updateId;
        if(studentList.search(updateId)){
            cout << "Enter new grade: ";
            cin >> newGrade;
            studentList.updateGrade(updateId, newGrade);
            cout << "Grade updated.\n";
        } else {
            cout << "Student not found.\n";
        }
        break;
    }
    case 6:
        // printing all students
        studentList.printList();
        break;
    case 7:
        return;
    default:
        cout << "\nInvalid Choice. Try Again.\n";
        break;}
 } while (true);
   
}
void advisingQueueMenu(AdvisingQueue& advisingQueue){
    do{
        cout << "\nAdvising Queue Menu\n";
        cout << "1. Add Student to Queue\n";
        cout << "2. Complete Request\n";
        cout << "3. Display Current\n";
        cout << "4. Return to Main Menu\n";
        cout << "\nEnter Choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                // Add student to queue
                advisingQueue.addToQueue();
                break;

            case 2:
                // Complete request
                advisingQueue.processNext();
                cout<<"Student remaining in queue: "<<advisingQueue.getQueueSize()<<"\n";
                break;

            case 3:
                // Display current student
                cout << "Current pending requests in the queue: " << advisingQueue.getQueueSize() << "\n";
                advisingQueue.printAll();
                break;

            case 4:
                // Return to Main Menu
                return;

            default:
                cout << "\nInvalid Choice. Try Again.\n";
        }
    } while (true);
}

void campusStatisticsMenu(StudentList& studentList, CampMap& campusMap, AdvisingQueue& advisingQueue) {
    cout<<"Campus Current Statistics:\n";
    cout<<"Total Students: "<<studentList.size()<<endl;
    studentList.averageGrade();
    cout<<"Current Pending Requests in Advising Queue: "<<advisingQueue.getQueueSize()<<"\n";
    cout<<"Map Statistics: \n";
    campusMap.mapStats();
        
}
