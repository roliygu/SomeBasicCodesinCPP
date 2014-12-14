//回溯法解作业调度问题:
// 解空间为n个作业集的排列解空间
//有两台机器.每个作业需要以此经过这两台及其才算完成
//对应有2*n的表格T,T[i][j]表示任务j经过机器i必须的时间
//求一个最佳调度顺序,使得所有任务完成后时间消耗最少 
#include<iostream>
using namespace std;
const int Max=256;
class Flowshop{
	private:
	public:
		int T[3][Max],manage[Max],endtimeM1,
			besttime,endtimeM2,len;
		Flowshop(int A[3][Max],int L);
		void gettime(int a,int b,int i);
		void Backtrack(int i,int a,int b);
		void show();
};
Flowshop::Flowshop(int A[3][Max],int L){
	len=L;
	for(int i=0;i<=len;i++){
		manage[i]=i;
		T[1][i]=A[1][i];
		T[2][i]=A[2][i];
	}
	endtimeM1=0;
	endtimeM2=0;
	besttime=INT_MAX;
}
void Flowshop::Backtrack(int i,int a,int b){
	if(i>len){
		for(int i=1;i<=len;i++)
		cout<<manage[i]<<" ";
		cout<<endl;
		besttime=b;
	}else{
		for(int j=i;j<=len;j++){
			int newa = a+T[1][manage[j]];
			int newb =((T[1][manage[j-1]])>(T[2][manage[j]]))?(newa+T[2][manage[j]]):(b+T[2][manage[j]]);
			if(newb<besttime){
				swap(manage[i],manage[j]);
				Backtrack(i+1,newa,newb);
				swap(manage[i],manage[j]);
			}
		}
	}
}
void Flowshop::show(){
	cout<<"all time :"<<besttime<<endl;
}
int main(){
	int A[3][Max];
	A[1][1]=2;
	A[1][2]=3;
	A[1][3]=2;
	A[2][1]=1;
	A[2][2]=1;
	A[2][3]=3;
	Flowshop C(A,3);
	C.Backtrack(1,0,C.T[1][C.manage[1]]);
	C.show();
	return 0;
} 