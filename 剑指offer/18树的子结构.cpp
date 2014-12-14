#include<iostream>

using namespace std;

typedef struct TreeNode{
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;
void BuildRoot1(TreeNode* root){
	root->data = 8;
	TreeNode *A = new TreeNode;
	A->data = 8;
	root->left = A;
	TreeNode *B = new TreeNode;
	B->data = 7;
	root->right = B;
	TreeNode *C = new TreeNode;
	C->data = 9;
	A->left = C;
	TreeNode *D = new TreeNode;
	D->data = 2;
	A->right = D;
	TreeNode *E = new TreeNode;
	E->data = 4;
	D->left = E;
	TreeNode *F = new TreeNode;
	F->data = 7;
	D->right = F;
}
int main(){


}