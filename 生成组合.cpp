#include<iostream>
using namespace std;
void create(int *A, int len, int r){
	int i=r;
	while(A[i]==(len-r+i))i--;
	if(i!=0){
		A[i]++;
		for(int j=i+1;j<=r;j++)
		A[j]=A[j-1]+1;
	}else
	return ;
}
void show(int *A){
	for(int i=1;i<=4;i++){
		cout<<A[i];
	}
	cout<<endl;
}
int main(){
	int a[10]={0,1,2,3,4,5,6};
	for(int i=1;i<=14;i++){
		create(a,6,4);
		show(a);
	}
	return 0;
}