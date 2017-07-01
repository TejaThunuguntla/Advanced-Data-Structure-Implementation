#include "BST.h"
#include <iostream>
#include <fstream>
#include <algorithm>

BST::BST()
{
	_root = NULL;
}

void BST::Insert(int _key, int _val)
{
	Node* newNode = new Node(_key, _val);
	
	if (_root == NULL)
		_root = newNode;
	else
	{
		Node* parent = _root;
		do
		{
			if (newNode->key <= parent->key)
			{
				if (parent->left == NULL)
				{
					parent->left = newNode;
					break;
				}
				parent = parent->left;
			}
			else
			{
				if (parent->right == NULL)
				{
					parent->right = newNode;
					break;
				}
				parent = parent->right;
			}

		} while (true);
	}
}

Node* BST::Search(int _key)
{
	Node* parent = _root;
	do
	{
		if (parent != NULL)
		{
			if (_key <= parent->key)
			{
				if (parent->key == _key)
					return parent;

				parent = parent->left;
			}
			else
				parent = parent->right;

		}
		else
			return NULL;

	} while (true);
}

Node* BST::InorderSuccessor(Node* _node, Node*& parent)
{
	Node* temp = NULL;
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

Node* BST::InorderPredecessor(Node* _node, Node*& parent)
{
	Node* temp = NULL;
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

void BST::Delete(int _key)
{
	Node* node = NULL;
	Node* parent = _root;
	Node* current = _root;
	do
	{
		if (current != NULL)
		{
			if (_key < current->key)
			{
				parent = current;
				current = current->left;
			}
			else if (current->key == _key)
			{
				Node* inorderParent = NULL;

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
							_root->key = node->key;
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
						_root->key = node->key;
						_root->value = node->value;
					}
					else parent->left == current ?
						parent->left->key = node->key, parent->left->value = node->value :
						parent->right->key = node->key, parent->right->value = node->value;
					return;
				}
				else 
				{ 
					node = InorderPredecessor(current, inorderParent); 

					if (inorderParent != NULL)
					{
						if (inorderParent == _root)
						{
							_root->key = node->key;
							_root->value = node->value;
							_root->left == node ? _root->left = node->left : _root->right = node->left;
							delete node;
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
						_root->key = node->key;
						_root->value = node->value;
					}
					else parent->right == current ?
						parent->right->key = node->key, parent->right->value = node->value :
						parent->left->key = node->key, parent->left->value = node->value;
					return;
				}
			}
			else
			{
				parent = current;
				current = current->right;
			}
		}
		else
			return;

	} while (true);
}

int BST::height()
{
	if (_root != NULL)
		return htrecur(_root);
	else return - 1;
}

int BST::htrecur(Node* node)
{
	if (node == NULL)
		return -1;

	return 1 + std::max(htrecur(node->left), htrecur(node->right));
}

void BST::Print(std::ostream& file, Node* parent)
{
	if (parent == NULL) {
		return;
	}
	Node* lchild = parent->left;
	Node* rchild = parent->right;

	if (lchild != NULL)
	{
		file << "node[style = filled, color = \".7 .3 1.0\"]\n";
		file << "\"" << parent->key << " , " << parent->value << "\"" << " -> " << "\"" << lchild->key << " , " << lchild->value << "\"" << "[tailport=sw]" << ";\n";
	}
	if (rchild != NULL)
	{
		file << "node[style = filled, color = lightgrey]\n";
		file << "\"" << parent->key << " , " << parent->value << "\"" << " -> " << "\"" << rchild->key << " , " << rchild->value << "\"" << "[tailport=se]" << ";\n";
	}
		if (lchild != NULL)
		Print(file, lchild);
	if (rchild != NULL)
		Print(file, rchild);
	return;
}

void BST::Show(std::string filename)
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