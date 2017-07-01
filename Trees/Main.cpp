#include "BST.h"
#include "kdTree.h"
#include <math.h>
#include <time.h>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

void TestI(BST& _tree, int n)
{
	std::vector<int> vec(n);
	vec[0] = 0;
	vec[1] = 1000;

	_tree.Insert(vec[0], 0);
	_tree.Insert(vec[1], 1);

	for (int i = 2; i < n; i++)
	{
		vec[i] = floor((vec[i - 1] + vec[i - 2]) / 2);
	}

	for (int i = 2; i < n; i++)
	{
		_tree.Insert(vec[i], i);
	}
}

void TestI(kdTree& _tree, int n)
{
	std::vector<int> vec(n);
	vec[0] = 0;
	vec[0] = 500;

	_tree.Insert(vec[0], 500 - vec[0], 0);
	_tree.Insert(vec[1], 500 - vec[1], 1);

	for (int i = 2; i < n; i++)
	{
		vec[i] = floor((vec[i - 1] + vec[i - 2]) / 2);
		_tree.Insert(vec[i], 500 - vec[i], i);
	}
}

void TestII(BST& _tree)
{
	srand(time(NULL));
	cout << "Num of nodes" << setw(12) << "Height" << setw(15) << "lgn" << setw(22) << "sqrt(n)" << endl;
	cout << "---------------------------------------------------------------" << endl;
	for (int i = 0; i < 200; i++)
	{
		int height = _tree.height();
		_tree.Insert(rand() % 5000, rand() % 2000);

		if (i % 20 == 0)
		{
			cout << setw(5) << i
				<< setw(16) << height;
				if (height > 0)
				{
					cout << setw(19) << fixed << setprecision(2) << log2(height)
						<< setw(19) << fixed << setprecision(2) << sqrt(height)
						<< endl;
				}
				else
				{
					cout << setw(18) << fixed << setprecision(2) << "NA"
						<< setw(19) << fixed << setprecision(2) << "NA"
						<< endl;
				}
		}
	}
}

void TestII(kdTree& _tree)
{
	srand(time(NULL));
	cout << "Num of nodes" << setw(12) << "Height" << setw(15) << "lgn" << setw(22) << "sqrt(n)" << endl;
	cout << "---------------------------------------------------------------" << endl;
	for (int i = 0; i < 200; i++)
	{
		int height = _tree.height();
		_tree.Insert(rand() % 50, rand() % 50, i);

		if (i % 20 == 0)
		{
			cout << setw(5) << i
				<< setw(16) << height;
				if (height > 0)
				{
					cout<< setw(19) << fixed << setprecision(2) << log2(height)
						<< setw(19) << fixed << setprecision(2) << sqrt(height)
						<< endl;
				}
				else
				{
					cout << setw(18) << fixed << setprecision(2) << "NA"
						<< setw(19) << fixed << setprecision(2) << "NA"
						<< endl;
				}
		}
	}
}

void TestIII(BST& _tree)
{
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		_tree.Insert(rand() % 1000, i + 1);
	}

	_tree.Show("t5-a");
	std::cout << "Generated t5-a.dot" << std::endl;
	_tree.Delete(_tree.root()->key);
	_tree.Show("t5-b");
	std::cout << "Generated t5-b.dot" << std::endl;
}

void TestIII(kdTree& _tree)
{
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		_tree.Insert(rand() % 1000, rand() % 1000, i + 1);
	}

	_tree.Show("t6-a");
	std::cout << "Generated t6-a.dot" << std::endl;
	_tree.Delete(_tree.root()->x, _tree.root()->y);
	_tree.Show("t6-b");
	std::cout << "Generated t6-b.dot" << std::endl;
}

void TestIV(BST& _tree)
{
	int _key = 0, _value = 0, search = 0;
	vector<int> vec;
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		vec.push_back(rand() % 100);
		_tree.Insert(vec[i], i + 1);
	}
	for (int i = 0; i < 10; i++)
	{
		_tree.Insert(vec[i], i + 11);
	}
	cout << setw(6) << "stage" << setw(20) << "data item at root" << setw(27) << "the root(after deletion)" << setw(20) << "search for data" << endl;
	cout << "--------------------------------------------------------------------------" << endl;

	for (int i = 0; i < 20; i++)
	{
		cout << setw(3);
		search = _key = _tree.root()->key;
		_value = _tree.root()->value;
		cout << i << setw(12) << "[ " << _key << " , " << _value << " ]";

		_tree.Delete(_key);
		if (_tree.height() >= 0)
		{
			_key = _tree.root()->key;
			_value = _tree.root()->value;
			cout << setw(15) << "[ " << _key << " , " << _value << " ]";
			Node* searchNode = _tree.Search(search);
			if (searchNode)
			{
				_key = searchNode->key;
				_value = searchNode->value;
				cout << setw(15) << "[ " << _key << " , " << _value << " ]" << endl;
			}
			else  cout << setw(18) << "*" << endl;
		}
		else
		{
			cout << setw(18) << "nil";
			cout << setw(23) << "nil" << endl;
		}
		//_tree.Show(string("test") + std::to_string(i));
	}
}

void TestIV(kdTree& _tree)
{
	int _x = 0, _y = 0, _value = 0, search[2] = { 0,0 };
	vector<int> vecX;
	vector<int> vecY;
	srand(time(NULL));

	for (int i = 0; i < 6; i++)
	{
		vecX.push_back(rand() % 100);
		vecY.push_back(rand() % 100);
		_tree.Insert(vecX[i], vecY[i], i + 1);
	}
	for (int i = 0; i < 6; i++)
	{
		vecY.push_back(rand() % 100);
		_tree.Insert(vecX[i], vecY[i + 6], i + 7);
	}
	for (int i = 0; i < 6; i++)
	{
		vecX.push_back(rand() % 100);
		_tree.Insert(vecX[i + 6], vecY[i], i + 13);
	}

	for (int i = 0; i < 18; i++)
	{
		cout << setw(3);
		search[0] = _x = _tree.root()->x;
		search[1] = _y = _tree.root()->y;
		_value = _tree.root()->value;
		cout << i;

		_tree.Delete(_x, _y);
		if (_tree.height() >= 0)
		{
			_x = _tree.root()->x;
			_y = _tree.root()->y;

			kNode* searchNode1 = _tree.Search(_x, search[1]);
			kNode* searchNode2 = _tree.Search(search[0], _y);
			if (searchNode1)
			{
				_x = searchNode1->x;
				_y = searchNode1->y;
				_value = searchNode1->value;
				cout << setw(10) << "[ " << _x << " , " << _y << " - " << _value << " ]" << endl;
			}
			else if (searchNode2)
			{
				_x = searchNode2->x;
				_y = searchNode2->y;
				_value = searchNode2->value;
				cout << setw(10) << "[ " << _x << " , " << _y << " - " << _value << " ]" << endl;
			}
			else  cout << setw(15) << "*" << endl;
		}
		else  cout << setw(15) << "*" << endl;

		if (i == 5)	_tree.Show("t8-a");
		else if (i == 11) _tree.Show("t8-b");
	}
}

int main()
{
	std::cout << "Test Case: 1\n" << "====================" << std::endl;
	BST tree1;
	TestI(tree1, 16);
	tree1.Show("t1");
	std::cout << "Generated t1.dot" << std::endl;

	std::cout << "\nTest Case: 2\n" << "====================" << std::endl;
	kdTree tree2;
	TestI(tree2, 16);
	tree2.Show("t2");
	std::cout << "Generated t2.dot" << std::endl;

	std::cout << "\nTest Case: 3\n" << "====================" << std::endl;
	BST tree3;
	TestII(tree3);

	std::cout << "\nTest Case: 4\n" << "====================" << std::endl;
	kdTree tree4;
	TestII(tree4);

	std::cout << "\nTest Case: 5\n" << "====================" << std::endl;
	BST tree5;
	TestIII(tree5);

	std::cout << "\nTest Case: 6\n" << "====================" << std::endl;
	kdTree tree6;
	TestIII(tree6);

	std::cout << "\nTest Case: 7\n" << "====================" << std::endl;
	BST tree7;
	TestIV(tree7);

	std::cout << "\nTest Case: 8\n" << "====================" << std::endl;
	kdTree tree8;
	TestIV(tree8);

	return 0;
}