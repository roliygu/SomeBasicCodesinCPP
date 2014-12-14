//counting the number of 1 in a bits
#include<iostream>
using namespace std;
inline int Count(int t){
	int num=0;
	while(t){
		t &= t-1;
		num++;
	}
	return num;
}
int main(){
	cout<<Count(256)<<endl;	
	return 0;
}