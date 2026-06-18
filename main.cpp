#include <iostream>
#include <fstream>

using namespace std;


#include <iostream>
#include <fstream>

using namespace std;
void loadFile();
void campusMapMenu();
void studentManagementMenu();
void advisingQueueMenu();

int main(){
     loadFile();
    int choice;

    do
    {
        cout << "\n========================================\n";
        cout << " Campus Exploration System\n";
        cout << "========================================\n";
        cout << "1. Campus Map\n";
        cout << "2. Student Management\n";
        cout << "3. Advising Queue\n";
        cout << "4. possible function\n";
        cout << "5. Exit\n";
        cout << "\nEnter Choice: ";

        cin >> choice;
                switch(choice)
        {

            case 1:
                campusMapMenu();
                break;

            case 2:
                studentManagementMenu();
                break;

            case 3:
                advisingQueueMenu();
                break;

            case 4:
                //possiblefuction();
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





//function to load a file and submenus
void loadFile()
{
    string fileName;

    cout << "Enter filename: ";
    cin >> fileName;

    ifstream inputFile(fileName);

    if (inputFile.is_open())
    {
        cout << "File loaded successfully.\n";

        inputFile.close();
    }
    else
    {
        cout << "Error opening file.\n";
    }
}

void campusMapMenu()
{
    cout << "\nCampus Map Menu\n";
    // Implement campus map functionality here
}

void studentManagementMenu()
{
    cout << "\nStudent Management Menu\n";
    // Implement student management functionality here
}

void advisingQueueMenu()
{
    cout << "\nAdvising Queue Menu\n";
    // Implement advising queue functionality here
}