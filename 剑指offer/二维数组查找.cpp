#include<iostream>
using namespace std;
int nums[5][5]={
	0,0,0,0,0,
	0,1,2,8,9,
	0,2,4,9,12,
	0,4,7,10,13,
	0,6,8,11,15
};
bool findNum(int x, int y, int number){
	if(x==5 || y==0)
		return false;
	else if(nums[x][y]==number)
		return true;		
	else{
		if(nums[x][y]>number)
			findNum(x,y-1,number);
		else
			findNum(x+1,y,number);
	}
}
int main(){
	bool check = findNum(1,4,7);
	cout<<check<<endl;
	return 0;
} 