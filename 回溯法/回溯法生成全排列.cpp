#include<iostream>
using namespace std;
int n = 4;
int A[10];
void F(int i){
	if(i==n){
		for(int i=1;i<=n;i++)
			cout<<A[i]<<" ";
		cout<<endl;
	}else{
		for(int j=i+1;j<=n;j++){
			swap(A[i],A[j]);
			F(i+1);
			swap(A[i],A[j]);
		}
	}
}
int main(){
	for(int i=0;i<=5;i++)A[i]=i;
	int a=1; 
	F(a);
	return 0;
}