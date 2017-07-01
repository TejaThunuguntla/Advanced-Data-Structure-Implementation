#ifndef PRIORITYQ_H
#define PRIORITYQ_H

#include <iostream>
#include <vector>

struct PQNode
{
	int distance;	// key
	int parent = -1;
	int node;		// value
};

class PriorityQueue
{
public:
	PriorityQueue(){}
	~PriorityQueue() {}
	int operator[](const int _node) const
	{
		for (auto node : _pQ)
			if (node->node == _node) 
				return node->distance;

		return -1;
	}
	void Insert(int key, int value, int parent = -1);
	int Minimum();
	bool Decrease(int key, int newVal, int parent = -1);
	int ExtractMin();
	int Size() { return _pQ.size(); }
	int getParent(int node);
	void Print();
private:
	void Heapify();
	void TestDown(int node);
	void TestUp(int node);
	std::vector<PQNode*> _pQ;
};

#endif