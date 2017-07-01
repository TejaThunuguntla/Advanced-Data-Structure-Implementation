#ifndef PRIORITYQ_H
#define PRIORITYQ_H

#include <iostream>
#include <vector>

struct PQNode
{
	int key;
	std::vector<int> value;
};

class PriorityQueue
{
public:
	PriorityQueue(){}
	~PriorityQueue() {}
	void Insert(int key, int value);
	std::vector<int> Minimum();
	bool Decrease(int old, int newVal);
	std::vector<int> ExtractMin();
	void Print();
private:
	void Heapify();
	void TestDown(int node);
	void TestUp(int node);
	std::vector<PQNode*> _pQ;
};

#endif