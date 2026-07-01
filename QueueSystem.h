#include <iostream>
#include <queue>
#include <string>
using namespace std;

class AdvisingQueue {
public:
	//adds student to queue
	void addToQueue();
	//prints next in queue data and removes the student from queue
	void processNext();
	//returns the queue size
	int getQueueSize();
	//prints all information of each student in queue
	void printAll();
private:
	//defines what a student is
	struct student { int id = 0; string issue = ""; };
	//declaring queue stl
	queue<student> advQueue;
};
