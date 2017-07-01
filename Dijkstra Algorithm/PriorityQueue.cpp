#include "PriorityQueue.h"

void PriorityQueue::Insert(int _distance, int _node, int parent)
{
	int len = _pQ.size();

	for (std::vector<PQNode*>::iterator iter = _pQ.begin(); iter != _pQ.end(); iter++)
	{
		if ((*iter)->node == _node)
		{
			(*iter)->distance = _distance;
			(*iter)->parent = parent;
			TestUp(iter - _pQ.begin());
			return;
		}
	}

	PQNode* newNode = new PQNode();
	newNode->distance = _distance;
	newNode->node = _node;
	newNode->parent = parent;
	_pQ.push_back(newNode);

	TestUp(len);
}

int PriorityQueue::Minimum()
{
	if (_pQ.size() > 0)
		return _pQ.front()->node;

	return -1;
}

int PriorityQueue::getParent(int node)
{
	if (_pQ.size() > 0)
	{
		for (std::vector<PQNode*>::iterator iter = _pQ.begin(); iter != _pQ.end(); iter++)
		{
			if ((*iter)->node == node)
			{
				return (*iter)->parent;
			}
		}
	}
	return -1;
}

bool PriorityQueue::Decrease(int _node, int _distance, int parent)
{
	if (_pQ.size() > 0)
	{
		for (std::vector<PQNode*>::iterator iter = _pQ.begin(); iter != _pQ.end(); iter++)
		{
			if ((*iter)->node == _node)
			{
				(*iter)->distance = _distance;
				(*iter)->parent = parent;
				Heapify();
				return true;
			}
		}
	}
	return false;
}

int PriorityQueue::ExtractMin()
{
	if (_pQ.size() > 0)
	{
		PQNode* output = _pQ.front();
		_pQ.erase(_pQ.begin());
		Heapify();
		return output->node;
	}

	return -1;
}

void PriorityQueue::Heapify()
{
	int len = _pQ.size();
	for (int i = len - 1; i >= 0; --i)
	{
		TestDown(i);
	}
}

void PriorityQueue::TestDown(int node)
{
	int len = _pQ.size();
	int leftChild = 2 * node + 1;
	int rightChild = 2 * node + 2;

	if (leftChild >= len)
		return; //index is a leaf

	int minIndex = node;

	if (_pQ[node]->distance > _pQ[leftChild]->distance)
	{
		minIndex = leftChild;
	}

	if ((rightChild < len) && (_pQ[minIndex]->distance > _pQ[rightChild]->distance))
	{
		minIndex = rightChild;
	}

	if (minIndex != node)
	{
		//need to swap
		PQNode* temp = _pQ[node];
		_pQ[node] = _pQ[minIndex];
		_pQ[minIndex] = temp;
		TestDown(minIndex);
	}
}

void PriorityQueue::TestUp(int node)
{
	if (node == 0)
		return;

	int parentIndex = (node - 1) / 2;

	if (_pQ[parentIndex]->distance > _pQ[node]->distance)
	{
		PQNode* temp = _pQ[parentIndex];
		_pQ[parentIndex] = _pQ[node];
		_pQ[node] = temp;
		TestUp(parentIndex);
	}
}

void PriorityQueue::Print()
{
	if (_pQ.size() > 0)
		for (std::vector<PQNode*>::iterator it = _pQ.begin(); it != _pQ.end(); it++)
		{
			std::cout << "   " << (*it)->distance << " - ";
			std::cout << (*it)->node << " ";
		}
	else std::cout << "empty queue";
	std::cout << std::endl;
}