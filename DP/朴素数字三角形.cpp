#include<iostream>
using namespace std;
int main(){
	int A[20]={7,3,8,8,1,0,2,7,4,4,4,5,2,6,5};
	int B[10][10];
	int k=0;
	for(int i=1;i<=5;i++)
		for(int j=1;j<=i;j++)
		B[i][j]=A[k++];
	for(int i=4;i>=1;i--)
		for(int j=1;j<=i;j++){
			int temp=(B[i+1][j]>B[i+1][j+1])?B[i+1][j]:B[i+1][j+1];
			B[i][j]+=temp;
		}
	cout<<B[1][1]<<endl;
	return 0;
}