#include<iostream>
using namespace std;

struct LNode{
	int m_Key;
	LNode* next;
};

void Prin(LNode* h){
	if(h==NULL)
		return;
	else{
		Prin(h->next);
		cout<<h->m_Key<<" ";
	}
}

int main(){
	LNode* head = new LNode();
	LNode* index = head;
	for(int i=0;i<10;i++){
		LNode* tem = new LNode();
		tem->m_Key=i;
		tem->next = NULL;
		index->next = tem;
		index = index->next;
	}
	//for(LNode* i = head; i!=NULL; i=i->next){
//		cout<<i->m_Key<<" ";
//	}
	Prin(head->next);
	return 0;
} 