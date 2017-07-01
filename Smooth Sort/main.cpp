#include <ctime> 
#include "PriorityQueue.h"
#include "LeonardoHeap.h"

void TestCase1(PriorityQueue& _pq)
{
	for (int i = 1; i <= 100; i++)
		_pq.Insert(100 - i + 1, i);
}

void TestCase2(PriorityQueue& _pq)
{
	for (int i = 1; i <= 1000; i++)
		_pq.Insert(1000 - i + 1, i);
}

void TestCase3(PriorityQueue& _pq)
{
	srand(time(NULL));
	for (int i = 1; i <= 500; i++)
		_pq.Insert(rand() % (1000 - 10) + 10, rand() % (1000 - 10) + 10);
}

void TestCase5(PriorityQueue& _pq)
{
	srand(time(NULL));
	for (int i = 0; i < 100; ++i)
	{
		switch (rand() % 4)
		{
		case 0:
			_pq.Minimum();
			break;
		case 1:
			_pq.Insert(rand() % (100 - 10) + 10, rand() % (100 - 10) + 10);
			break;
		case 2:
			_pq.ExtractMin();
			break;
		case 3:
			_pq.Decrease(rand() % (100 - 10) + 10, rand() % 10 + 1);
			break;
		}
		if (i % 20 == 0)
			_pq.Print();
	}
}

void TestCase6(SmoothSort& _ss)
{
	for (int i = 1; i <= 1000; i++)
		_ss.Insert(1000 - i + 1);
}

void TestCase7(SmoothSort& _ss)
{
	srand(time(NULL));
	for (int i = 1; i <= 2000; i++)
		_ss.Insert(i);

	for (int i = 0; i < 10; i++)
	{
		int num1 = rand() % 2000;
		int num2 = rand() % 2000;
		if (num1 != num2)
		{
			int temp = _ss[num1];
			_ss[num1] = _ss[num2];
			_ss[num2] = temp;
		}
	}
}

void TestCase8(SmoothSort& _ss)
{
	srand(time(NULL));
	for (int i = 1; i <= 2000; i++)
		_ss.Insert(i);
	for (int i = 0; i < 20; i++)
	{
		int num1 = rand() % 1000;
		int num2 = rand() % 1000;
		int num3 = rand() % 1000;

		int temp = _ss[num1];
		_ss[num1] = _ss[num2];
		temp = _ss[num2];
		_ss[num2] = _ss[num3];
		_ss[num3] = temp;
	}
}

void TestCase9(SmoothSort& _ss)
{
	srand(time(NULL));
	for (int i = 1; i <= 3193; i++)
		_ss.Insert(rand() % 10000 + 1);
}

void TestCase10(SmoothSort& _ss)
{
	srand(time(NULL));
	for (int i = 1; i <= 5166; i++)
		_ss.Insert(rand() % 10000 + 1);
}

int main()
{
	std::cout << "Test Case: 1 \n================" << std::endl;
	PriorityQueue pq1;
	TestCase1(pq1);
	std::vector<int> output1 = pq1.ExtractMin();
	std::cout << "Extract all Minimum : ";
	for (std::vector<int>::iterator iter = output1.begin(); iter != output1.end(); iter++)
		std::cout << *iter << " ";
	std::cout << "\nInserted [1,0]" << std::endl;
	pq1.Insert(1, 0);
	output1 = pq1.ExtractMin();
	std::cout << "Extract all Minimum : ";
	for (std::vector<int>::iterator iter = output1.begin(); iter != output1.end(); iter++)
		std::cout << *iter << " ";
	
	std::cout << "\n\nTest Case: 2 \n================" << std::endl;
	PriorityQueue pq2;
	TestCase2(pq2);
	std::vector<int> output2 = pq2.Minimum();
	std::cout << "All Minimum : ";
	for (std::vector<int>::iterator iter = output2.begin(); iter != output2.end(); iter++)
		std::cout << *iter << " ";
	std::cout << "\nInserted [1,1] [1,2] ... [1,30]" << std::endl;
	for (int i = 1; i <= 30; i++)
		pq2.Insert(1, i);
	output2 = pq2.ExtractMin();
	std::cout << "Extract all Minumum: ";
	for (std::vector<int>::iterator iter = output2.begin(); iter != output2.end(); iter++)
		std::cout << *iter << " ";
	output2 = pq2.Minimum();
	std::cout << "\nAll Minimum: ";
	for (std::vector<int>::iterator iter = output2.begin(); iter != output2.end(); iter++)
		std::cout << *iter << " ";

	std::cout << "\n\nTest Case: 3 \n================" << std::endl;
	PriorityQueue pq3;
	TestCase3(pq3);
	std::vector<int> output3;
	std::cout << "Extract all Minumum (5 times): " << std::endl;
	for (int i = 0; i < 5; i++)
	{
		output3 = pq3.ExtractMin();
		for (std::vector<int>::iterator iter = output3.begin(); iter != output3.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
	}
	std::cout << "Decreased a random key to 5" << std::endl;
	while (!pq3.Decrease(rand() % (1000 - 10) + 10, 5)) {}
	output3 = pq3.Minimum();
	std::cout << "All Minimum: ";
	for (std::vector<int>::iterator iter = output3.begin(); iter != output3.end(); iter++)
		std::cout << *iter << " ";

	std::cout << "\n\nTest Case: 4 \n================" << std::endl;
	PriorityQueue pq4;
	TestCase3(pq4);
	int count = 0;
	std::cout << "Decreased 10 random keys" << std::endl;
	while (count <= 10)
	{
		pq4.Decrease(rand() % (1000 - 10) + 10, rand() % 9);
		count++;
	}
	std::vector<int> output4;
	std::cout << "Extract all Minimum (5 times): " << std::endl;
	for (int i = 0; i < 5; i++)
	{
		output4 = pq4.ExtractMin();
		for (std::vector<int>::iterator iter = output4.begin(); iter != output4.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
	}

	std::cout << "\n\nTest Case: 5 \n================" << std::endl;
	PriorityQueue pq5;
	TestCase5(pq5);

	std::cout << "\n\nTest Case: 6 \n================" << std::endl;
	SmoothSort _heap6;
	TestCase6(_heap6);
	_heap6.Sort();
	_heap6.Print();

	std::cout << "\n\nTest Case: 7 \n================" << std::endl;
	SmoothSort _heap7;
	TestCase7(_heap7);
	_heap7.Sort();
	_heap7.Print();

	std::cout << "\n\nTest Case: 8 \n================" << std::endl;
	SmoothSort _heap8;
	TestCase8(_heap8);
	_heap8.Sort();
	_heap8.Print();

	std::cout << "\n\nTest Case: 9 \n================" << std::endl;
	SmoothSort _heap9;
	TestCase9(_heap9);
	_heap9.Sort();
	_heap9.Print();

	std::cout << "\n\nTest Case: 10 \n================" << std::endl;
	SmoothSort _heap10;
	TestCase10(_heap10);
	_heap10.Sort();
	_heap10.Print();
}