#include "QueueSystem.h"

//gets the information to create and add a new student struct to the advising queue
void AdvisingQueue::addToQueue() {
	student tempS;
	string inIssue;
	//geting sutdent info
	cout << "Please enter student ID: ";
	cin >> tempS.id;
	cin.ignore();
	cout << "Please enter advising issue: ";
	getline(cin, inIssue);
	tempS.issue = inIssue;
	//pusing the student into the queue
	advQueue.push(tempS);
	cout << "Student was added " << advQueue.size() << ": place in queue\n";
}

//processes the student in the queue by displaying info and removing them from queue
void AdvisingQueue::processNext() {
	//printing student information
	if (!advQueue.empty()) {
		cout << "Student ID: " << advQueue.front().id << endl;
		cout << "Advising issue: " << advQueue.front().issue << endl;
		//asking the user if the issue was resolved if yes, the student is removed from the queue
		cout << "was the issue resolved |y| |n| : ";
		char choice;
		cin >> choice;
		if (choice == 'y' || choice == 'Y') {
			advQueue.pop();
			cout << "Student was removed form queue\n";
		}
		else {
			cout << "Keeping student at front of queue\n";
		}
	}
	else {
		cout << "Queue is empty\n";
	}
}
//returns the size of the queue
int AdvisingQueue::getQueueSize() {
	return advQueue.size();
}
//prints all the information of each student in the queue
void AdvisingQueue::printAll() {
	if (!advQueue.empty()) {
		queue<student> tempQueue;
		tempQueue = advQueue;
		cout << "Printing all issues in advising queue: \n";
		while (!tempQueue.empty()) {
			cout << "student Id: " << tempQueue.front().id << endl;
			cout << "Student issue: " << tempQueue.front().issue << endl << endl;
			tempQueue.pop();
		}
	}
	else {
		cout << "Queue is empty\n";
	}
}
