#include<iostream>
using namespace std;

int* pretension(int* Num, int len){
	int start=1,end=len-1;
	while(start<end){
		while(Num[start]<Num[0])
			start++;
		while(Num[end]>Num[0])
			end--;
		if(start>=end)
			break;
		else
			swap(Num[start],Num[end]);
	}
	swap(Num[0],Num[start-1]);
	return &Num[start];
}
void quicksort(int* Num, int len){
	if(len==0)
		return;
	int* index = pretension(Num, len);
	if(index-Num>0)
		quicksort(Num,index-Num,)
		
}

int main(){
	int num[20]={5,6,8,9,10,2,3,6,5,1,2};
	pretension(num,11);
	for(int i=0;i<11;i++)
		cout<<num[i]<<" ";
	return 0;
} 