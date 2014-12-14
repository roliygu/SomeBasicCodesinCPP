#include "BinaryTree.h"

BinaryTree::~BinaryTree(){
	//cout<<"delete the node: "<<this->m_data<<endl;
	//if(this->m_left){
	//	m_left->~BinaryTree();
	//}	
	//if(this->m_right){
	//	m_right->~BinaryTree();
	//}	
		cout<<this->m_data<<" ";
		//cout<<-1<<" ";
}
type BinaryTree::GetData(){
	return this->m_data;
}
BinaryTree* BinaryTree::GetLeftChildren(){
	return this->m_left;
}
BinaryTree* BinaryTree::GetRightChildren(){
	return this->m_right;
}
void BinaryTree::SetData(type data){
	this->m_data = data;
	return;
}
void BinaryTree::SetLeftChildren(BinaryTree* node){
	this->m_left = node;
}
void BinaryTree::SetRightChildren(BinaryTree* node){
	this->m_right = node;
}
void BinaryTree::InitNode(type data, BinaryTree *left, BinaryTree *right){
	SetData(data);
	SetLeftChildren(left);
	SetRightChildren(right);
}
void BinaryTree::DFS(void (*VisitFunction)(BinaryTree&)){
	(*VisitFunction)(*this);
  	if(this->m_left)
  		this->m_left->DFS(VisitFunction);
  	if(this->m_right)
  		this->m_right->DFS(VisitFunction);
}
void BinaryTree::BFS(void (*VisitFunction)(BinaryTree&)){
	queue<BinaryTree*> Que;
	Que.push(this);
	while(!Que.empty()){
		BinaryTree* temp = Que.front();
		Que.pop();
		VisitFunction(*temp);
		if(temp->m_left)
			Que.push(temp->m_left);
		if(temp->m_right)
			Que.push(temp->m_right);
	}
}
void BinaryTree::ClearTree(){
	if(this->m_left){
		this->m_left->ClearTree();
		return;
	}
	if(this->m_right){
		this->m_right->ClearTree();
		return;
	}
	this->~BinaryTree();
}