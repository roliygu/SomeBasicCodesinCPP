//queue 用front获得队首元素,然后top弹出,才能获得第二个"队首"
//引用做函数参数,需在函数外先对其赋初值,然后函数修改才有效
//vector不是数据类型,所以没有 vector a[10]这样表示10个vector组成数组的方式,只能写作
//vector <T> a[10] 
//遍历vector的所用元素,使用t.begin(),t.end()和迭代器 
//sort(start,end,cmp)cmp{return a<b;}时结果是升序 


#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;


const int maxn=1024;
int A[maxn][4];

void input(int A[maxn][4], int &len){
	cin>>len;
	for(int i=1;i<=len;i++){
		cin>>A[i][0]>>A[i][1]>>A[i][2];
	}
}


class Set{
	private:
		int S[maxn],len;
	public:
		Set(int l);
		int Find(int n);
		void Union(int a,int b);
		void show();
};
Set::Set(int l){
	for(int i=1;i<=l;i++)
		S[i]=i;
	len=l;
}
int Set::Find(int n){
	return S[n];
}
void Set::Union(int a,int b){
	//将跟b同集合的所有元素都并入a集合
	int temp=S[b];
	for(int i=1;i<=len;i++){
		if(S[i]==temp)
			S[i]=S[a];
	} 
}
void Set::show(){
	for(int i=1;i<=len;i++)
	cout<<S[i]<<' ';
}


class GNode{
	public:
		int end,weight;
};
class Node{
	public:
		int color,d,parent;
		Node(){
			color=-1;
			d=0;
			parent=-1;
		}
};
class Edge{
	public:
		int a,b,w;
		bool select;
};
class Graph{
	private:
		vector <GNode> map[maxn];
		Node VNode[maxn];
		int Elen,Vlen;
		queue <int> V;
	public:		
		
		Edge ENode[maxn];
		void setup(int T[maxn][4],int len);
		void setupENode(int T[maxn][4],int len);
		void Kruskal(int T[maxn][4],int len);
		void BFS();
		void DFS();
		void SubDFS(int i);
		void show();
	
};
bool cmp(Edge a,Edge b){
	return a.w<b.w;
}
void Graph::setupENode(int T[maxn][4],int len){
	Elen=len;
	int maxx=-1;
	for(int i=1;i<=len;i++){
		if(T[i][0]>maxx)maxx=T[i][0];
		ENode[i].a=T[i][0];
		ENode[i].b=T[i][1];
		ENode[i].w=T[i][2];
		ENode[i].select=false;
	}
	Vlen=maxx;
}
void Graph::Kruskal(int T[maxn][4],int len){
	setupENode(T,len);
	int k=0;
	sort(ENode+1,ENode+len+1,cmp);
	Set *tem=new Set(Vlen); 
	for(int i=1;i<=Elen;i++){
		if(k==(VNode-1))break;
		int x = tem->Find(ENode[i].a);
		int y = tem->Find(ENode[i].b);
		if(x!=y){
			tem->Union(x,y);
			k++;
			ENode[i].select=true;
		}
	}
}
void Graph::setup(int T[maxn][4],int len){
	Elen=len;
	int maxx=-1;
	for(int i=1;i<=len;i++){
		int start = T[i][0];
		if(start>maxx)maxx=start;
		GNode e;
		e.end=T[i][1];
		e.weight=T[i][2];
		map[start].push_back(e);
	}
	Vlen=maxx;
}
void Graph::BFS(){
	for(int i=1;i<=Vlen;i++)VNode[i].color=-1;
	V.push(1);
	while(V.size()!=0){
		int i = V.front();
		V.pop();
		cout<<i<<" ";
		for(vector <GNode>::iterator j=map[i].begin();j<map[i].end();j++){
			int temp = (*j).end;
			if(VNode[temp].color==-1){
				V.push(temp);
				VNode[temp].color=0;
			}		
		}
		VNode[i].color=1;
	}
}
void Graph::DFS(){
	for(int i=1;i<=Vlen;i++)VNode[i].color=-1;
	for(int i=1;i<=Vlen;i++){
		if(VNode[i].color==-1)
			SubDFS(i);
	}
}
void Graph::SubDFS(int i){
	cout<<i<<" ";
	VNode[i].color=0;
	for(vector <GNode>::iterator j=map[i].begin();j<map[i].end();j++){
		if(VNode[(*j).end].color==-1)
			SubDFS((*j).end);
		VNode[(*j).end].color=1;
	}
}
void Graph::show(){
	for(int i=1;i<=Vlen;i++){
		cout<<map[i].size()<<endl;
		for(vector <GNode>::iterator j=map[i].begin();j<map[i].end();j++){
			GNode p=*j;
			cout<<p.end<<" "<<p.weight<<" ";
		}
		cout<<endl;	
	}
}


int main(){	
	int len=0;
	input(A,len);
	Graph T;
	T.Kruskal(A,len);
	return 0;
}