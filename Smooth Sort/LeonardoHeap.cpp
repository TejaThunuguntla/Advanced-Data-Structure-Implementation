#include <algorithm>
#include <numeric>
#include "LeonardoHeap.h"

int leonardoNum[20];

inline bool isLeonardoNum(int _num)
{
	return std::find(std::begin(leonardoNum) + 2, std::end(leonardoNum), _num) != std::end(leonardoNum);
}

LeonardoHeap::LeonardoHeap()
{
	leonardoNum[0] = 1;
	leonardoNum[1] = 1;

	for (int i = 2; i < 20; i++)
	{
		leonardoNum[i] = leonardoNum[i - 1] + leonardoNum[i - 2] + 1;
	}
}

void LeonardoHeap::Insert(int newVal)
{
	int len = _heap.size();
	_heap.push_back(newVal);
	TestUp(len);
}

int LeonardoHeap::Maximum()
{
	return _heap.front();
}

int LeonardoHeap::ExtractMax()
{
	int key = 0;
	if (_heap.size() > 0)
	{
		key = _heap.front();
		_heap.erase(_heap.begin());
		Heapify();
	}
	return key;
}

void LeonardoHeap::Heapify()
{
	int len = _heap.size();
	for (int i = len - 1; i >= 0; --i)
	{
		TestDown(i);
	}
}

void LeonardoHeap::TestDown(int node)
{
	int len = _heap.size();
	int leftChild = 2 * node + 1;
	int rightChild = 2 * node + 2;

	if ((leftChild >= len) || rightChild < 0 || leftChild < 0)
		return; 

	int maxIndex = node;

	if (_heap[node] < _heap[leftChild])
	{
		maxIndex = leftChild;
	}

	if ((rightChild < len) && (_heap[maxIndex] < _heap[rightChild]))
	{
		maxIndex = rightChild;
	}

	if (maxIndex != node)
	{
		int temp = _heap[node];
		_heap[node] = _heap[maxIndex];
		_heap[maxIndex] = temp;
		TestDown(maxIndex);
	}
}

void LeonardoHeap::TestUp(int node)
{
	if (node == 0)
		return;

	int parentIndex = (node - 1) / 2;

	if (_heap[parentIndex] < _heap[node])
	{
		int temp = _heap[parentIndex];
		_heap[parentIndex] = _heap[node];
		_heap[node] = temp;
		TestUp(parentIndex);
	}
}

void LeonardoHeap::Merge(LeonardoHeap& _heap1, LeonardoHeap& _heap2)
{
	int size1 = _heap1.Size();
	for (int i = 0; i < size1; i++)
		this->Insert(_heap1.ExtractMax());
	size1 = _heap2.Size();
	for (int j = 0; j < size1; j++)
		this->Insert(_heap2.ExtractMax());
}

SmoothSort::SmoothSort()
{
	comparisions = 0;
}

void SmoothSort::Insert(int val)
{
	inp.push_back(val);
}

void SmoothSort::Sort()
{
	int inpSize = inp.size();
	for (int i = 0; i < inpSize; i++)
	{
		LeonardoHeap _hp;
		_hp.Insert(inp[i]);
		_heaps.push_back(_hp);
		_flag.push_back(1);
		BuildHeap();
	}
	for (int i = inpSize - 1; i >= 0; i--)
	{
		inp[i] = _heaps[_heaps.size() - 1].ExtractMax();

		if (_heaps[_heaps.size() - 1].Size() == 0)
			_heaps.pop_back();
		if (_heaps.size() > 1)
			selection_sort(_heaps.size());
		comparisions++;
	}
}

void SmoothSort::BuildHeap()
{
	for (int n = 0; n < _flag.size(); n++)
	{
		if (isLeonardoNum(std::accumulate(std::begin(_flag) + n, std::end(_flag), 0)))
		{
			comparisions++;
			_heaps[_heaps.size() - 1].Merge(_heaps[n], _heaps[n + 1]);
			_flag[_flag.size() - 1] = _heaps[_heaps.size() - 1].Size();
			_heaps.erase(_heaps.begin() + n, _heaps.begin() + n + 2);
			_flag.erase(_flag.begin() + n, _flag.begin() + n + 2);
			return;
		}
	}
	selection_sort(_heaps.size());	
}

void SmoothSort::selection_sort(int size)
{
	int min;
	for (int i = 0; i < size - 1; ++i)
	{
		min = i;

		for (int j = i + 1; j < size; ++j)
		{
			if (_heaps[j].Maximum() < _heaps[min].Maximum())
			{
				min = j;
			}
		}
		if (min != i)
		{
			int root1 = _heaps[i].ExtractMax();
			int root2 = _heaps[min].ExtractMax();
			_heaps[i].Insert(root2);
			_heaps[min].Insert(root1);
			comparisions++;
		}
	}
}

void SmoothSort::Print()
{
	std::cout << "Num of comparisions : " << comparisions << std::endl;
	std::cout << "Shortened listing :" << std::endl;

	for (int i = 0; i < inp.size(); i+=20)
	{
		std::cout << inp[i] << " ";
	}
	std::cout << std::endl;
}