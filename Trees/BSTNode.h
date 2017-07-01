#ifndef BST_NODE
#define BST_NODE

#include <iostream>

struct Node
{
	int key;
	int value;
	Node* left;
	Node* right;
	Node(){}
	Node(int key, int value)
	{
		this->key = key;
		this->value = value;
		left = NULL;
		right = NULL;
	}
};

struct kNode
{
	kNode(int x, int y, int value)
	{
		this->x = x;
		this->y = y;
		this->value = value;
		left = NULL;
		right = NULL;
	}

	int operator[](int arg)
	{
		if (arg % 2 == 0)
			return this->x;
		else
			return this->y;
	}
	int x;
	int y;
	int value;
	kNode* left;
	kNode* right;
};

#endif // !BST_NODE