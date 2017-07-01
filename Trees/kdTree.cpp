#include "kdTree.h"
#include <iostream>
#include <fstream>
#include <algorithm>

kdTree::kdTree()
{
	_root = NULL;
}

void kdTree::Insert(int _x, int _y, int _value)
{
	kNode* newNode = new kNode(_x, _y, _value);

	if (_root == NULL)
		_root = newNode;
	else
	{
		kNode* parent = _root;
		for (int i = 0;; i++)
		{
			if (newNode->operator[](i) <= parent->operator[](i))
			{
				if (parent->left == NULL)
				{
					parent->left = newNode;
					return;
				}
				parent = parent->left;
			}
			else
			{
				if (parent->right == NULL)
				{
					parent->right = newNode;
					return;
				}
				parent = parent->right;
			}
		}
	}
}

kNode* kdTree::Search(int _x, int _y)
{
	kNode* parent = _root;
	kNode* newNode = new kNode(_x, _y, -1);

	for (int i = 0;; i++)
	{
		if (parent != NULL)
		{
			if (newNode->operator[](i) <= parent->operator[](i))
			{
				i++;
				if (newNode->operator[](i) == parent->operator[](i))
					return parent;
				parent = parent->left;
				i--;
			}
			else
				parent = parent->right;
		}
		else return NULL;
	}
}

kNode* kdTree::InorderSuccessor(kNode* _node, kNode*& parent)
{
	kNode* temp = NULL;
	parent = _node;
	if (_node->right != NULL)
	{
		temp = _node->right;
		do
		{
			if (temp->left == NULL)
				return temp;
			parent = temp;
			temp = temp->left;

		} while (true);
	}
	return temp;
}

kNode* kdTree::InorderPredecessor(kNode* _node, kNode*& parent)
{
	kNode* temp = NULL;
	parent = _node;
	if (_node->left != NULL)
	{
		temp = _node->left;
		do
		{
			if (temp->right == NULL)
				return temp;
			parent = temp;
			temp = temp->right;

		} while (true);
	}
	return temp;
}

void kdTree::Delete(int _x, int _y)
{
	kNode* node = NULL;
	kNode* parent = _root;
	kNode* current = _root;
	for (int i = 0;;i++)
	{
		if (current != NULL)
		{
			if (current->x == _x && current->y == _y)
			{
				kNode* inorderParent = NULL;

				if (height() == 0)
				{
					_root = NULL;
					return;
				}

				if (current->right != NULL)
				{
					node = InorderSuccessor(current, inorderParent);

					if (inorderParent != NULL)
					{
						if (inorderParent == _root)
						{
							_root->x = node->x;
							_root->y = node->y;
							_root->value = node->value;
							_root->right == node ? _root->right = node->right : _root->left = node->right;
							delete node;
							return;
						}
						if (inorderParent->right == NULL)
						{
							inorderParent->right = node->right;
							inorderParent->left = NULL;
						}
						else inorderParent->left = node->right;
					}

					if (current == _root)
					{
						_root->x = node->x;
						_root->y = node->y;
						_root->value = node->value;
					}
					else parent->left == current ?
						parent->left->x = node->x, parent->left->y = node->y, parent->left->value = node->value :
						parent->right->x = node->x, parent->right->y = node->y, parent->right->value = node->value;
					delete node;
					return;
				}
				else
				{
					node = InorderPredecessor(current, inorderParent);

					if (inorderParent != NULL)
					{
						if (inorderParent == _root)
						{
							_root->x = node->x;
							_root->y = node->y;
							_root->value = node->value;
							_root->left == node ? _root->left = node->left : _root->right = node->left;
							return;
						}
						if (inorderParent->left == NULL)
						{
							inorderParent->left = node->left;
							inorderParent->right = NULL;
						}
						else inorderParent->right = node->left;
					}

					if (current == _root)
					{
						_root->x = node->x;
						_root->y = node->y;
						_root->value = node->value;
					}
					else parent->right == current ?
						parent->right->x = node->x, parent->right->y = node->y, parent->right->value = node->value :
						parent->left->x = node->x, parent->left->y = node->y, parent->left->value = node->value;				
					return;
				}
			}
			else if (returnKey(_x, _y, i) < current->operator[](i))
			{
				parent = current;
				current = current->left;
			}
			else
			{
				parent = current;
				current = current->right;
			}
		}
		else
			return;
	}
}

int kdTree::returnKey(int _x, int _y, int arg)
{
	if (arg % 2 == 0)
		return _x;
	else
		return _y;
}

int kdTree::height()
{
	if (_root != NULL)
		return htrecur(_root);
	else return -1;
}

int kdTree::htrecur(kNode* node)
{
	if (node == NULL)
		return -1;

	return 1 + std::max(htrecur(node->left), htrecur(node->right));
}

void kdTree::Print(std::ostream& file, kNode* parent)
{
	if (parent == NULL) {
		return;
	}
	kNode* lchild = parent->left;
	kNode* rchild = parent->right;

	if (lchild != NULL)
	{
		file << "node[style = filled, color = \".7 .3 1.0\"]\n";
		file << "\"" << parent->x << "," << parent->y << "," << parent->value << "\"" << " -> " << "\"" << lchild->x << "," << lchild->y << "," << lchild->value << "\"" << "[tailport=sw]" << ";\n";
	}
	if (rchild != NULL)
	{
		file << "node[style = filled, color = lightgrey]\n";
		file << "\"" << parent->x << "," << parent->y << "," << parent->value << "\"" << " -> " << "\"" << rchild->x << "," << rchild->y << "," << rchild->value << "\"" << "[tailport = se]"<< ";\n";
	}
	if (lchild != NULL)
		Print(file, lchild);
	if (rchild != NULL)
		Print(file, rchild);
	return;
}

void kdTree::Show(std::string filename)
{
	std::ofstream _file;
	_file.open(filename + ".dot");
	_file << "digraph G { \n";
	_file << "rankdir=TD; \n";
	_file << "constraint=true;\n";
	_file << "ordering=out;\n";
	Print(_file, _root);
	_file << "}";
	_file.close();
}