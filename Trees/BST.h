#ifndef BST_H
#define BST_H

#include "BSTNode.h"

class BST
{
public:
	BST();
	void Insert(int _key, int _val);
	void Delete(int _key);
	Node* Search(int _key);
	void Show(std::string filename);
	int height();
	Node* root() { return this->_root; }
private:
	Node* _root;
	Node* InorderSuccessor(Node* _node, Node*& parent);
	Node* InorderPredecessor(Node* _node, Node*& parent);
	int htrecur(Node* _node);
	void Print(std::ostream& file, Node* parent);
};

#endif
