#include<iostream>
using namespace std;
const int Max=256;
class Graph{
	private:
		int mark[Max][Max];
		int Vlen,colornum,color[Max];
	public:
		Graph(int T[Max][Max],int L,int m);
		void Backtrack(int t);
};
Graph::Graph(int T[Max][Max],int L,int m){
	Vlen=L;
	colornum=m;
	for(int i=1;i<=Vlen;i++)
		for(int j=1;j<=Vlen;j++)
			mark[i][j]=T[i][j];
	memset(color,0,sizeof(int)*Vlen);
}
void Graph::Backtrack(int t){
	if(t>Vlen){
		for(int i=1;i<=Vlen;i++)
			cout<<color[i]<<" ";
		cout<<endl;
	}else{
		for(int j=1;j<=colornum;j++){
			bool vec=false;
			for(int i=1;i<=Vlen;i++)
				if(mark[t][i]&&(j==color[i])){
					vec=true;
					break;
				}
			if(!vec){
				color[t]=j;
				Backtrack(t+1);
			}	
			color[t]=0;
		}
	}	
}
int main(){
	int A[Max][Max];
	for(int i=1;i<=5;i++)
	for(int j=1;j<=5;j++)
	cin>>A[i][j];
	Graph B(A,5,4);
	B.Backtrack(1);
	return 0;
} 