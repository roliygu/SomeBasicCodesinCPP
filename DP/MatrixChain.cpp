#include<iostream>
using namespace std;
const int Max=200;
class MatrixChain{
	private:
		int res[Max][Max],mark[Max][Max],num;
	public:
		MatrixChain(int L,int *T);
		void Traceback(int i,int j);
		void show();
};
MatrixChain::MatrixChain(int L,int *T){
	num=L;
	for(int i=0;i<=num;i++)
		res[i][i]=0;	
	for(int t=1;t<num;t++){
		for(int i=1;i<=num-t;i++){
			int j=i+t,k=i;
			res[i][j]=T[i-1]*T[k]*T[j]+res[i][k]+res[k+1][j];
			mark[i][j]=k;
			for(k=i+1;k<=j;k++){
				int temp=T[i-1]*T[k]*T[j]+res[i][k]+res[k+1][j];
				if(temp<res[i][j]){
					res[i][j]=temp;
					mark[i][j]=k;
				}
			}
		}
	}
}
void MatrixChain::Traceback(int i,int j){
	if(i==j)return;
	Traceback(i,mark[i][j]);
	Traceback(mark[i][j]+1,j);
	cout<<"A"<<i<<","<<mark[i][j]<<" and A"<<(mark[i][j]+1)<<","<<j<<endl;
}
void MatrixChain::show(){
	for(int i=1;i<=num;i++){
		for(int j=1;j<=num;j++)
			cout<<res[i][j]<<" ";
		cout<<endl;
	}
}
int main(){
	int a[10]={30,35,15,5,10,20,25};
	MatrixChain B(6,a);
	B.Traceback(1,6);
	return 0;
} 