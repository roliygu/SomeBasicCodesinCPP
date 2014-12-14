#ifndef _ROLIY_BINARY_TREE
#define _ROLIY_BINARY_TREE

#include <iostream>
#include <queue>
using namespace std;

typedef int type;

class BinaryTree{
private:
	type m_data;
	BinaryTree* m_left;
	BinaryTree* m_right;	
public:
	BinaryTree():m_left(NULL),m_right(NULL){}; 
	~BinaryTree();

	type GetData();
	BinaryTree* GetLeftChildren();
	BinaryTree* GetRightChildren();

	void SetData(type data);
	void SetLeftChildren(BinaryTree* node);
	void SetRightChildren(BinaryTree* node);

	void InitNode(type data, BinaryTree* left, BinaryTree* right);
	
	void DFS(void (*VisitFunction)(BinaryTree&));
	void BFS(void (*VisitFunction)(BinaryTree&));
	void ClearTree();
};

#endif