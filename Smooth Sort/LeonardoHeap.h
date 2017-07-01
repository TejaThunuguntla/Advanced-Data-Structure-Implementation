#ifndef LEONARDOHEAP_H
#define LEONARDOHEAP_H

#include <iostream>
#include <vector>

class LeonardoHeap
{
public:
	LeonardoHeap();
	~LeonardoHeap() {}
	void Insert(int key);
	int Maximum();
	int ExtractMax();
	void Merge(LeonardoHeap& _heap1, LeonardoHeap& _heap2);
	int Size() { return _heap.size(); }
	void Heapify();
private:
	void TestDown(int node);
	void TestUp(int node);
	std::vector<int> _heap;
};

class SmoothSort
{
public:
	SmoothSort();
	int operator[](int num) const { return inp[num]; }
	int& operator[](int num) {	return this->inp[num];	}
	void Insert(int val);
	void Sort();
	void Print();
private:
	int comparisions;
	std::vector<int> _flag;
	std::vector<LeonardoHeap> _heaps;
	std::vector<int> inp;
	void BuildHeap();
	void selection_sort(int size);
};

#endif