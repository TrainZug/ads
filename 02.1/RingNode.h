#pragma once
#include <string>
using namespace std;
class RingNode
{
private:
	int OldAge;
	string Description;
	string SymbolicData;
	RingNode* next;
public: 
	RingNode();
	RingNode(string, string);
	RingNode(int, string, string);
	int getAge();
	void setAge(int);
	string getDescription();
	void setDescription(string);
	string getData();
	void setData(string);
	RingNode* getNext();
	void setNext(RingNode*);
};

