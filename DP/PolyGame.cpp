//此程序还不是正确版,不想写了...
//一个n边型,每条边有一个权值,每个节点是'+'或'*',求最优划分,使得最后计算式
//得到最大值和最小值 
#include<iostream>
using namespace std;
const int Max=256;
class PolyGame{
	private:
		char op[Max];
		int num[Max],len,res[Max][Max][2];
	public:
		PolyGame(int *N,char *C,int L);
		void MinMax(int i,int j,int s,int& minf,int& maxf);
		int setup();
		void show();
};
PolyGame::PolyGame(int *N,char *C,int L){
	len=L;
	for(int i=1;i<=len;i++){
		num[i]=N[i-1];
		op[i]=C[i-1];
	}
}
void PolyGame::MinMax(int i,int j,int s,int& minf,int& maxf){
	int e[4];
	int a=res[i][s][0],b=res[i][s][1],
			r=(i+s-1)%len+1,c=res[r][j-s][0],d=res[r][j-s][1];
	if(op[r]=='+'){
		minf=a+c;
		maxf=b+d;
	}else{
		e[1]=a*c;e[2]=a*d;e[3]=b*c;e[4]=b*d;
		minf=e[1];maxf=e[r];
		for(int r=2;r<len;r++){
			if(minf>e[r])minf=e[r];
			if(maxf<e[r])maxf=e[r];
		}
	}
}
int PolyGame::setup(){
	int minf,maxf;
	for(int j=2;j<=len;j++)
		for(int i=1;i<=len;i++)
			for(int s=1;s<j;s++){
				MinMax(i,j,s,minf,maxf);
				if(res[i][j][0]>minf)res[i][j][0]=minf;
				if(res[i][j][1]<maxf)res[i][j][1]=maxf;
			}
		int temp = res[1][len][1];
		for(int i=2;i<=len;i++)
			if(temp<res[i][len][1])temp=res[i][len][1];
		return temp;
}
void PolyGame::show(){
	for(int i=1;i<=len;i++)
		cout<<op[i]<<" ";
	for(int i=1;i<=len;i++){
		for(int j=1;j<=len;j++)
			cout<<res[i][j][0]<<" ";
		cout<<endl;
	}
	cout<<endl;
	for(int i=1;i<=len;i++){
		for(int j=1;j<=len;j++)
			cout<<res[i][j][1]<<" ";
		cout<<endl;
	}
}
int main(){
	int a[10]={1,2,3,4,5};
	char b[10]={'*','+','*','+','*','+'};
	PolyGame C(a,b,5);
	cout<<C.setup()<<endl;
	return 0;
}