#include<iostream>
using namespace std;
inline void Mul(int *A, int *B, int *C){
	//A和B是乘积项,C是结果项 
	memset(C,0,sizeof(int)*130);
	for(int i=0;i<=130;i++){
		if(A[i]!=0)
			for(int j=0;j<=130;j++){
				if(B[j]!=0){
					int temp = i+j;
					if(temp>130)break;
					else{
						C[temp]+=A[i]*B[j];
					}
				}
			}
	}
}
inline void generate(int *B,int n,int m){
	//此函数是根据要求重写的多项式生成函数,注意不要越界 
	//n表示第n个多项式,m表示数组最大限 
	memset(B,0,sizeof(int)*(m+10));
	B[0]=1;
	for(int i=1;i*n<=m;i++){
		int temp = i*n;
		B[temp]=1;
	}
}
int main(){
	int B[130],C[130],D[130],n;
	while(cin>>n){
		if(n==1){
			cout<<1<<endl;
			continue;
		}
		for(int i=0;i<=2;i++){
			memset(D,0,sizeof(int)*130);
			int maxn = n;
			generate(B,1,maxn);
			for(int j=2;j<=maxn;j++){
				generate(C,j,maxn);
				Mul(B,C,D);
				memcpy(B,D,sizeof(int)*130);
			}
		}
		cout<<D[n]<<endl;
	}	
	return 0;
}