#include<iostream>
using namespace std;

struct BTNode{
	int m_Key;
	BTNode* left;
	BTNode* right;
};

void DFS(BTNode *head){
	if(head==NULL)
		return;
	else{
		cout<<head->m_Key<<" ";
		DFS(head->left);
		DFS(head->right);
	}
}
BTNode* buildBT(int* pre, int preLen, int* mid, int midLen){
	if(pre == NULL || mid==NULL || preLen==0 || midLen==0)
		return 0;
	else{
		BTNode* tem = new BTNode();
		tem->m_Key = pre[0];
		tem->left = NULL;
		tem->right = NULL;
		int* index = find(mid, mid+midLen, pre[0]);
		int leftSize = index-mid, rightSize = midLen-(index-mid+1);
		if(leftSize>0)
			tem->left = buildBT(pre+1, leftSize, mid, leftSize);
		if(rightSize>0)
			tem->right = buildBT(pre+leftSize+1, rightSize, mid+leftSize+1, rightSize);
		return tem;
	}	
}
int main(){
	int num1[20]={1,2,4,7,3,5,6,8},num2[20]={4,7,2,1,5,3,8,6};
	BTNode* head = buildBT(num1, 8, num2, 8);
	DFS(head);
	return 0;
}