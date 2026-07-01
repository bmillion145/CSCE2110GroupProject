#include <iostream>
#include <queue>
#include <string>
using namespace std;

class AdvisingQueue {
public:
	void addToQueue();
	void processNext();
	int getQueueSize();
	void printAll();
private:
	struct student { int id = 0; string issue = ""; };
	queue<student> advQueue;
};
