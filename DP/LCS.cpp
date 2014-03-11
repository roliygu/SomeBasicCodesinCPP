#include<iostream>
#include<string>
using namespace std;
const int Max=200;

class LCS{
	private:
		char A[Max],B[Max];
		int Alen,Blen,mark[Max][Max],maxLen;
	public:
		LCS(char *X,char *Y,int Xlen,int Ylen);
		void setupMark();
		void show(int i,int j);
};
LCS::LCS(char *X,char *Y,int Xlen,int Ylen){
	Alen=Xlen,Blen=Ylen;
	memcpy(A+1,X,sizeof(char)*Alen);
	memcpy(B+1,Y,sizeof(char)*Blen);
	for(int i=0;i<Xlen+5;i++)
		for(int j=0;j<Ylen+5;j++)
			mark[i][j]=0;
}
void LCS::setupMark(){
	for(int i=1;i<=Alen;i++)
		for(int j=1;j<=Blen;j++){
			if(A[i]==B[j])
				mark[i][j]=mark[i-1][j-1]+1;
			else{
				mark[i][j]=(mark[i-1][j]>mark[i][j-1])?mark[i-1][j]:mark[i][j-1];
			}
		}
	maxLen=mark[Alen][Blen];
}
void LCS::show(int i,int j){
	if(i==0||j==0)
		return ;
	if(mark[i][j]==mark[i-1][j-1]+1){
		cout<<A[i]<<" ";
		show(i-1,j-1);
	}else if(mark[i][j]==mark[i][j-1]){
		show(i,j-1);
	}else{
		show(i-1,j);
	}
	
}
int main(){
	char a[10]={'a','b','c','d','a','b'};
	char b[10]={'b','c','d','b'};
	LCS C(a,b,6,4);
	C.setupMark();
	C.show(6,4);
	return 0;
}