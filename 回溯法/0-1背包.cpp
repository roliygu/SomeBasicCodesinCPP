#include<iostream>
#include<algorithm>
using namespace std;
const int Max=1024;
class tempclass{
	public:
		int a;
		float b;
		tempclass(){};
};
bool cmp(tempclass A,tempclass B){
	return A.b>B.b;
}
class Knapsack{
	private:
		int len,allVolum,bound,max,
			wealth[Max],volume[Max],mark[Max];
	public:
		Knapsack(int L,int aV,int *A,int *B);
		void setbound();
		void Backtrack(int t,int m,int c);
		void show();
};
Knapsack::Knapsack(int L,int aV,int *A,int *B){
	len=L;
	allVolum=aV;
	for(int i=1;i<=len;i++){
		wealth[i]=A[i-1];
		volume[i]=B[i-1];
	}
	memset(mark,0,sizeof(int)*(len+5));
	max=INT_MIN;
}
void Knapsack::setbound(){
	tempclass A[len+5];
	for(int i=1;i<=len;i++){
		A[i].a=volume[i];
		A[i].b=wealth[i]*1.0/volume[i];
	}
	sort(A+1,A+len+1,cmp);
	int i=1,vo=0;
	for(;i<=len;i++){
		int newvo=vo+A[i].a;
		if(newvo>=allVolum)break;
		else{
			vo=newvo;
			bound+=(A[i].a*A[i].b);
		}
	}
	float t=(allVolum-vo)*1.0*A[i].b;
	bound+=t;
}
void Knapsack::Backtrack(int t,int m,int c){
	if(t>len){
		if(m>max){
			max=m;
			show();
		}
	}
	else{
		for(int i=0;i<2;i++){
			mark[t]=i;
			int newm=m+i*wealth[t];
			int newc=c-i*volume[t];
			if(newc>=0&&newm<bound)
				Backtrack(t+1,newm,newc);
			mark[t]=0;
		}
	}
}
void Knapsack::show(){
//	for(int i=1;i<=len;i++)
//		cout<<wealth[i]<<" ";
//	cout<<endl;
//	for(int i=1;i<=len;i++)
//		cout<<volume[i]<<" ";
//cout<<bound<<endl;
for(int i=1;i<=len;i++)
cout<<mark[i]<<" ";
cout<<endl;
cout<<max<<endl;
}
int main(){
	int A[10]={9,10,7,4};
	int B[10]={3,5,2,1};
	Knapsack C(4,7,A,B);
	C.setbound();
	C.Backtrack(1,0,7);
	return 0;
}