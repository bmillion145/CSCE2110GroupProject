#include "QueueSystem.h"


void AdvisngQueue::addToQueue() {
	student tempS;
	cout << "Please enter student ID: ";
	cin >> tempS.id;
	cout << "Please enter advising issue: ";
	getline(cin, tempS.issue);
	advQueue.push(tempS);
	cout << "Student was added \n" << advQueue.size()+1 << ": place in queue\n";
}

void AdvisngQueue::processNext() {
	cout << "Student ID: " << advQueue.front().id << endl;
	cout << "Advising issue: " << advQueue.front().issue << endl;
	cout << "was the issue resullved |y| |n| : ";
	char choice;
	cin >> choice;
	if (choice == 'y' || choice == 'Y') {
		advQueue.pop();
		cout << "Studnet was removed form queue\n";
	}
	else if ( choice == 'n'|| choice == 'N') {
		cout << "Keeping student at front of queue\n";
	}
}

int AdvisngQueue::getQueueSize() {
	return advQueue.size() + 1;
}

void AdvisngQueue::printAll() {
	queue<student> tempQueue;
	tempQueue = advQueue;
	cout << "Printing all issues in advising queue: \n";
	while (!tempQueue.empty()) {
		cout << "student Id: " << tempQueue.front().id <<endl;
		cout << "Student issue: " << tempQueue.front().issue << endl <<endl;
	}
}
