#include<iostream>
using namespace std;
typedef int Element;
#define maxn 100
int compare(Element A, Element B){
	//这里仅适用于int和char,另外的类型再改 
	if(A>B)return 1;
	else if (A==B)return 0;
	else return -1;
}
long int Factorial(int j){
	//long int 所能表示的最大阶乘认为是 12! 
	long int temp=1;
	for(int i=2;i<=j;i++)
	temp*=i;
	return temp;
}

class Array{
	public:
		int data[maxn];
		int len;
		Array(int l);
		Array(int *A, int l);
		void Show();
};
Array::Array(int l){
	//默认情况下,数据部分的元素是int 
	this->len=l;
	memset(this->data, 0, sizeof(int)*maxn);
	for(int i=1;i<=len;i++)
		data[i]=i;
}
Array::Array(int *A, int l){
	len=l;
	memcpy(data+1, A, sizeof(int)*len);
}
void Array::Show(){
	for(int i=1;i<=len;i++)
	cout<<data[i]<<" ";
	cout<<endl;
}

class ArrayOrdinal:public Array{
	public:
		long int OrdinalNumber;
		int OrdinalArray[maxn];
		ArrayOrdinal(int l):Array(l){};
		ArrayOrdinal(int *A, int l):Array(A, l){};
		void NumbertoOrdinal();
		void OrdinaltoNumber();
		void OrdinaltoArray();
		void ArraytoOrdinal();
		void NumbertoArray();
		void ArraytoNumber();
		void Showall();
};
void ArrayOrdinal::NumbertoOrdinal(){
	int j=2;
	long int temp = OrdinalNumber;
	for(int i=len-1;i>=1;i--){
		OrdinalArray[i]=temp%j;
		temp-=(temp%j);
		temp/=j;
		j++;
	}
}
void ArrayOrdinal::OrdinaltoNumber(){
	OrdinalNumber=0;
	int j=1;
	for(int i=len-1;i>=1;i--){
		long int temp = j*OrdinalArray[i];
		OrdinalNumber+=temp;
		j++;
	}
}
void ArrayOrdinal::Showall(){
	cout<<OrdinalNumber<<" ";
	for(int i=1;i<=len-1;i++)cout<<OrdinalArray[i];
	cout<<" ";
	Show();
	cout<<endl;
}
void ArrayOrdinal::ArraytoOrdinal(){
	//data仅限int 
	for(int i=1;i<=len;i++){
		int num=0;
		for(int j=1;j<i;j++){
			if(data[j]>data[i])num++;
		}
		OrdinalArray[data[i]]=num;
	}
}
void ArrayOrdinal::OrdinaltoArray(){
	memset(data, 0, sizeof(int)*(len+5));
	for(int i=1;i<=len;i++){
		int num=0;
		for(int j=1;j<=len;j++){
			if(data[j]==0)num++;
			if(num==(OrdinalArray[i]+1)){
				data[j]=i;
				break;
			}
		}
	}
}
void ArrayOrdinal::NumbertoArray(){
	NumbertoOrdinal();
	OrdinaltoArray();
}
void ArrayOrdinal::ArraytoNumber(){
	ArraytoOrdinal();
	OrdinaltoNumber();
}

class ArrayDictionary:public Array{
	public:
		void generate();
		ArrayDictionary(int l):Array(l){};
		ArrayDictionary(int *A, int l):Array(A, l){};
};
void ArrayDictionary::generate(){
	//序列是严格递减时,保持原序列不变 
	int m=len-1;
	int n=0;
	while((data[m]>data[m+1])&&(m>=1)){
		m--;
	}
	if(m==0)return;
	for(int i=len;i>=m;i--){
		if(data[i]>data[m]){
			int temp=data[i];
			data[i]=data[m];
			data[m]=temp;
			break;
		}
	}
	for(int i=m+1;i<=(m+len)/2;i++){
		int temp=data[i];
		data[i]=data[m+1+len-i];
		data[m+1+len-i]=temp;
	}
}

class Node{
	//false表示方向向左,true表示向右 
	public:
		bool direction;
		int data;
		Node *next;
		Node(int d);
};
Node::Node(int d){
	data=d;
	next=NULL;
}
class ArrayChange{
	private:
		Node *first;
		int len;
	public:
		ArrayChange(int l);
		ArrayChange(int *A, int l);
		void Show();
		
};
ArrayChange::ArrayChange(int l){
	len=l;
	first=new Node(0);
	Node *p=first;
	for(int i=1;i<=l;i++){
		Node *temp = new Node(i);
		p->next = temp;
		p=p->next;
	}
}
ArrayChange::ArrayChange(int *A, int l){
	len=l;
	first = new Node(0);
	Node *p=first;
	for(int i=0;i<len;i++){
		Node *temp = new Node(A[i]);
		p->next= temp;
		p = p->next;
	}
}
void ArrayChange::Show(){
	for(Node *i=first->next;i->next!=NULL;i->next=i->next->next){
		cout<<i->direction<<" ";
	}
	cout<<endl;
	for(Node *i=first->next;i->next!=NULL;i->next=i->next->next){
		cout<<i->data<<" ";
	}
	cout<<"\n"<<endl;
}

int main(){
	char A[4]={'a','b','c','d'};
	int AA[9]={1,4,2,3,5};
	ArrayChange *B=new ArrayChange(AA,5);
	B->Show();
	return 0;
}