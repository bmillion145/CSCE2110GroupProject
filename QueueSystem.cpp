#include "QueueSystem.h"


void AdvisingQueue::addToQueue() {
	student tempS;
	string inIssue;
	cout << "Please enter student ID: ";
	cin >> tempS.id;
	cin.ignore();
	cout << "Please enter advissing issue: ";
	getline(cin, inIssue);
	tempS.issue = inIssue;
	advQueue.push(tempS);
	cout << "Student was added " << advQueue.size() << ": place in queue\n";
}

void AdvisingQueue::processNext() {
	cout << "Student ID: " << advQueue.front().id << endl;
	cout << "Advising issue: " << advQueue.front().issue << endl;
	cout << "was the issue resolved |y| |n| : ";
	char choice;
	cin >> choice;
	if (choice == 'y' || choice == 'Y') {
		advQueue.pop();
		cout << "Student was removed form queue\n";
	}
	else if (choice == 'n' || choice == 'N') {
		cout << "keeping student at front of queue\n";
	}
}

int AdvisingQueue::getQueueSize() {
	return advQueue.size();
}

void AdvisingQueue::printAll() {
	queue<student> tempQueue;
	tempQueue = advQueue;
	cout << "Printing all issues in advising queue: \n";
	while (!tempQueue.empty()) {
		cout << "student Id: " << tempQueue.front().id << endl;
		cout << "Student issue: " << tempQueue.front().issue << endl << endl;
		tempQueue.pop();
	}
}