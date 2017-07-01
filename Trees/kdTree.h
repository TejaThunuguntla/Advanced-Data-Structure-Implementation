#ifndef KDTREE
#define KDTREE

#include "BSTNode.h"

class kdTree
{
public:
	kdTree();
	void Insert(int _x, int _y, int _val);
	void Delete(int _x, int _y);
	kNode* Search(int _x, int _y);
	void Show(std::string filename);
	int height();
	kNode* root() { return this->_root; }
private:
	kNode* _root;
	int returnKey(int _x, int _y, int i);
	kNode* InorderSuccessor(kNode* _node, kNode*& parent);
	kNode* InorderPredecessor(kNode* _node, kNode*& parent);
	int htrecur(kNode* node);
	void Print(std::ostream& file, kNode* parent);
};

#endif // !KDTREE
