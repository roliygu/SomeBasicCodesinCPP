#include<iostream>
using namespace std;
typedef char Element;
#define maxn 1000
class Array{
	public:
		Element data[maxn];
		int len;
		Array(int l);
		Array(Element *A, int l);
		void Show();
};
int compare(Element A, Element B){
	//这里仅适用于int和char,另外的类型再改 
	if(A>B)return 1;
	else if (A==B)return 0;
	else return -1;
}
Array::Array(int l){
	//默认情况下,数据部分的元素是int 
	this->len=l;
	memset(this->data, 0, sizeof(int)*maxn);
	for(int i=1;i<=len;i++)
		data[i]=i;
}
Array::Array(Element *A, int l){
	len=l;
	memcpy(data+1, A, sizeof(Element)*len);
}
void Array::Show(){
	for(int i=1;i<=len;i++)
	cout<<data[i]<<" ";
	cout<<endl;
}
class ArrayDictionary:public Array{
	public:
		void generate();
		ArrayDictionary(int l):Array(l){};
		ArrayDictionary(Element *A, int l):Array(A, l){};
};
void ArrayDictionary::generate(){
	//序列是严格递减时,保持原序列不变 
	int m=len-1;
	int n=0;
	while((1==compare(data[m], data[m+1]))&&(m>=1)){
		m--;
	}
	if(m==0)return;
	for(int i=len;i>=m;i--){
		if(data[i]>data[m]){
			Element temp=data[i];
			data[i]=data[m];
			data[m]=temp;
			break;
		}
	}
	for(int i=m+1;i<=(m+len)/2;i++){
		Element temp=data[i];
		data[i]=data[m+1+len-i];
		data[m+1+len-i]=temp;
	}
}
int main(){
	char A[4]={'a','b','c','d'};
	int AA[9]={1,2,3,4,5};
	ArrayDictionary *B=new ArrayDictionary(A,4);
	//Array *C=new Array(4);
	for(int i=1;i<=23;i++){
		B->generate();
		B->Show();
	}
	//C->Show();
	return 0;
}