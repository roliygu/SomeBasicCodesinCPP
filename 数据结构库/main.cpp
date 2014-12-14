#include "BinaryTree.h"


void Visit(BinaryTree &node){
	cout<<node.GetData()<<" ";
}

int main(){
	BinaryTree a,b,c,d,e,f;
	a.InitNode(1,&b,&c);
	b.InitNode(2,&d,NULL);
	c.InitNode(3, &e, NULL);
	d.InitNode(4, NULL, NULL);
	e.InitNode(5, NULL, &f);
	f.InitNode(6, NULL, NULL);
	a.ClearTree();
	
	return 0;
}

