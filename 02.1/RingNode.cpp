#include "RingNode.h"

RingNode::RingNode()
{
	OldAge = 0;
	Description = "";
	SymbolicData = "";
	next = nullptr;
}

RingNode::RingNode(string desc, string data)
{
	OldAge = 0;
	Description = desc;
	SymbolicData = data;
}

RingNode::RingNode(int age, string desc, string data)
{
	OldAge = age;
	Description = desc;
	SymbolicData = data;
}

int RingNode::getAge()
{
	return OldAge;
}

void RingNode::setAge(int age)
{
	OldAge = age;
}

string RingNode::getDescription()
{
	return Description;
}

void RingNode::setDescription(string d)
{
	Description = d;
}

string RingNode::getData()
{
	return SymbolicData;
}

void RingNode::setData(string d)
{
	SymbolicData = d;
}

RingNode* RingNode::getNext()
{
	return next;
}

void RingNode::setNext(RingNode* n)
{
	next = n;
}
