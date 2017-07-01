#include "PriorityQueue.h"

void PriorityQueue::Insert(int _key, int _val)
{
	int len = _pQ.size();

	for (std::vector<PQNode*>::iterator iter = _pQ.begin(); iter != _pQ.end(); iter++)
	{
		if ((*iter)->key == _key)
		{
			(*iter)->value.push_back(_val);
			return;
		}
	}

	std::vector<int> newVec;
	newVec.push_back(_val);
	PQNode* newNode = new PQNode();
	newNode->key = _key;
	newNode->value = newVec;
	_pQ.push_back(newNode);

	TestUp(len);
}

std::vector<int> PriorityQueue::Minimum()
{
	if (_pQ.size() > 0)
		return _pQ.front()->value;

	std::vector<int> temp;
	return temp;
}

bool PriorityQueue::Decrease(int oldVal, int newVal)
{
	if (_pQ.size() > 0)
	{
		std::vector<PQNode*>::iterator old = _pQ.begin();
		std::vector<PQNode*>::iterator newPtr = _pQ.begin();

		for (std::vector<PQNode*>::iterator iter = _pQ.begin(); iter != _pQ.end(); iter++)
		{
			if ((*iter)->key == oldVal)
				old = iter;

			if ((*iter)->key == newVal)
				newPtr = iter;
		}

		if (newPtr != _pQ.begin())
		{
			(*newPtr)->value.insert((*newPtr)->value.end(), (*old)->value.begin(), (*old)->value.end());
			_pQ.erase(old);
			return true;
		}
		else
		{
			(*old)->key = newVal;
			Heapify();
			return true;
		}
	}
	return false;
}

std::vector<int> PriorityQueue::ExtractMin()
{
	if (_pQ.size() > 0)
	{
		PQNode* output = _pQ.front();
		_pQ.erase(_pQ.begin());
		Heapify();
		return output->value;
	}
	std::vector<int> temp;
	return temp;
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
		return; 

	int minIndex = node;

	if (_pQ[node]->key > _pQ[leftChild]->key)
	{
		minIndex = leftChild;
	}

	if ((rightChild < len) && (_pQ[minIndex]->key > _pQ[rightChild]->key))
	{
		minIndex = rightChild;
	}

	if (minIndex != node)
	{
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

	if (_pQ[parentIndex]->key > _pQ[node]->key)
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
			std::cout << "   " << (*it)->key << " - ";
			for (std::vector<int>::iterator itVal = (*it)->value.begin(); itVal != (*it)->value.end(); itVal++)
				std::cout << *itVal << " ";
		}
	else std::cout << "empty queue";
	std::cout << std::endl;
}