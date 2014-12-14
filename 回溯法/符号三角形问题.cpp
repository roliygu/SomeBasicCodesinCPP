#include<iostream>
using namespace std;
const int Max=256;
class Triangle{
	private:
		int sum,len,half,count;
		int T[Max][Max];
	public:
		Triangle(int n);
		void Backtrack(int i,int count);
		void show();
};
Triangle::Triangle(int n){
	memset(T,0,sizeof(int)*Max*Max);
	len=n;
	int temp = (1+n)*n/2;
	if(temp%2!=0)
		cout<<"不能构成三角"<<endl;
	else
		sum=0;
	half=temp/2; 
}
void Triangle::Backtrack(int t,int count){
	if((count>half)||(t*(t-1)/2-count)>half)return ;
	if(t>len)
		sum++;
	else
		for(int i=0;i<2;i++){
			T[1][t]=i;
			int newcount = count+i;
			for(int j=2;j<=t;j++){
				T[j][t+1-j]=T[j-1][t+1-j]^T[j-1][t+2-j];
				newcount+=T[j][t+1-j];
			}
			Backtrack(t+1,newcount);
		}
}
void Triangle::show(){
	cout<<"count :"<<sum<<endl;
	cout<<len;
}
int main(){
	Triangle A(4);
	A.Backtrack(1,0);
	A.show();
	return 0;
}