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


const int EMax=1024;//EMax表示数组的最大边界 
const int VMax=200;
const int Max=999999;//Max表示可能出现的最大数值 
int A[EMax][4];

class Set{
	private:
		int S[EMax],len;
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
	//此为邻接表中的节点 
	public:
		int end,weight;
};
class Node{
	public:
		int color,d,parent;
		Node(){
			//Dijkstra算法中,color=-1表示未确定到源点最短距离的点集
			//,color=0表示已确定的点集,d表示到源点的距离,d=-1表示源
			//点不可达,parent表示单源最短路径的前驱
			//搜索中,color=-1表示当前未知的点,color=0表示当前正在处
			//理的点,color=1表示处理完成的点 
			color=-1;
			d=-1;
			parent=-1;
		}
};
class Edge{
	public:
		int a,b,w;
		bool select;
		void show(){
			cout<<'('<<a<<' '<<b<<' '<<w<<')'<<endl;
		};
};

class Graph{
	private:
		int Elen,Vlen;
		Node VNode[VMax];
		Edge ENode[EMax];	
		vector <GNode> map[VMax];		
		int Matrix[VMax][VMax];
		int networkMap[VMax][VMax];	
		int matchMap[VMax][VMax];
		queue <int> V;
	public:	
		int IMatrix[VMax][VMax];
		Edge IENode[EMax];
		inline void inputIMatrix(int len);		
		inline void inputIENode(int len);
		inline void IMatrix2Matrix();
		inline void IMatrix2ENode();
		inline void IENode2ENode();
		inline void IENode2Matrix();
		void setup();//构造成邻接表	
		void BFS();
		void DFS();
		void SubDFS(int i);
		void topogySort();
		void Kruskal();
		void Dijkstra(int n);
		inline int DijkstraFindAvailableShortest(int n);
		void Floyd();
		inline void setnetworkMap();
		void EdmondKarp(int start,int end);
		bool EKPathFindBFS(int map[VMax][VMax],int *p,int *flag,int start,int end);
		void setMatchMap();
		void binaryMaximumMatch();
		void show();	
};
bool cmp(Edge a,Edge b){

	return a.w<b.w;
}
inline void Graph::inputIMatrix(int len){
	//这里的len表示点的个数,点之间无边用0表示
	Vlen=len;
	for(int i=1;i<=len;i++)
		for(int j=1;j<=len;j++){
			cin>>IMatrix[i][j];	
		}
}
inline void Graph::inputIENode(int len){
	//len表示边的条数
	Elen=len;
	int maxx=-1;
	for(int i=1;i<=len;i++){
		cin>>IENode[i].a>>IENode[i].b>>IENode[i].w;
		IENode[i].select=false;
		if(IENode[i].b>maxx)maxx=IENode[i].b;
		if(IENode[i].a>maxx)maxx=IENode[i].a;
	}
	Vlen=maxx;
}
inline void Graph::IMatrix2Matrix(){
	//没有边的值为0
	int k=0;
	for(int i=1;i<=Vlen;i++)
		for(int j=1;j<=Vlen;j++){
			Matrix[i][j]=IMatrix[i][j];
			if(IMatrix[i][j]!=0)k++;
		}
	Elen=k;
}
inline void Graph::IMatrix2ENode(){
	//使用此函数之前一定要确认邻接矩阵中什么值代表有边,
	//这里默认0表示没有边,非0值(包括负数)代表边上权值
	int k=1;
	for(int i=1;i<=Vlen;i++)
		for(int j=1;j<=Vlen;j++)
			if(IMatrix[i][j]!=0){
				ENode[k].a=i;
				ENode[k].b=j;
				ENode[k].w=IMatrix[i][j];
				ENode[k].select=false;
				k++;
			}
	Elen=k-1;
}
inline void Graph::IENode2ENode(){
	for(int i=1;i<=Elen;i++){
		ENode[i].a=IENode[i].a;
		ENode[i].b=IENode[i].b;
		ENode[i].w=IENode[i].w;
		ENode[i].select=false;
	}
}
inline void Graph::IENode2Matrix(){
	//如果点间没有边,则将其矩阵值设为0,
	//对角线值为0,其他值根据输入的边集确定
	for(int i=0;i<VMax;i++)
	for(int j=0;j<VMax;j++)
		Matrix[i][j]=0;
	for(int i=1;i<=Elen;i++){
		Matrix[IENode[i].a][IENode[i].b]=IENode[i].w;
	}
	for(int i=1;i<=Vlen;i++)Matrix[i][i]=0;
}
void Graph::setup(){
	for(int i=1;i<=Elen;i++){
		int start = IENode[i].a;
		GNode e;
		e.end=IENode[i].b;
		e.weight=IENode[i].w;
		map[start].push_back(e);
	}
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
void Graph::topogySort(){
	//通过邻接矩阵拓扑排序,有向无环图;
	for(int i=1;i<=Vlen;i++)
		for(int j=1;j<=Vlen;j++)
			//这里将有向边值(不管权值是多少)设置为1,邻接矩阵中没有边的设置为0
			Matrix[i][j]=(Matrix[i][j]==0)?0:1;	
	for(int i=1;i<=Vlen;i++)
		//Matrix[0][i]是标志位,标记了是否已经从图中去掉点i,0表示未去掉,1表示已去掉;
		Matrix[0][i]=0;
	for(int i=1;i<=Vlen;i++){
		//当前要删除的点是第i个点
		for(int j=1;j<=Vlen;j++){
			if(Matrix[0][j]==0){
				int sum=0;
				for(int k=1;k<=Vlen;k++)sum+=Matrix[k][j];
				if(sum==0){
					Matrix[0][j]=1;
					cout<<j<<" ";
					for(int k=1;k<=Vlen;k++){
						if(Matrix[j][k]!=0)Matrix[j][k]--;
					}
					break;	
				}
			}
		}
	}
}
void Graph::Kruskal(){
	//无向图
	int k=0;
	sort(ENode+1,ENode+Elen+1,cmp);
	Set tem(Vlen); 
	for(int i=1;i<=Elen;i++){
		if(k==(Vlen-1))return;
		int x = tem.Find(ENode[i].a);
		int y = tem.Find(ENode[i].b);
		if(x!=y){
			tem.Union(x,y);
			k++;
			ENode[i].select=true;
			cout<<'('<<ENode[i].a<<' '<<ENode[i].b<<')'<<endl;
		}
	}
}
void Graph::Dijkstra(int n){
	//得到源点n到其他各点的最短距离和路径	
	VNode[n].color=0;
	VNode[n].d=0;
	for(vector <GNode>::iterator j=map[n].begin();j<map[n].end();j++){
		//用邻接表将与源点直接相连的点距离刷新 
		VNode[(*j).end].d=(*j).weight;
		VNode[(*j).end].parent=n;
	}		
	int t =DijkstraFindAvailableShortest(n);
 	while(t!=-1){
 		for(vector <GNode>::iterator j=map[t].begin();j<map[t].end();j++){
		 	int point = (*j).end;
		 	if(VNode[point].d<0){
	 			VNode[point].d=VNode[t].d+(*j).weight;
	 			VNode[point].parent=t;
	 		}else if(VNode[point].d>0){
		 		if((VNode[point].d)>(VNode[t].d+(*j).weight)){
		 			VNode[point].d=VNode[t].d+(*j).weight;
		 			VNode[point].parent=t;
		 		}
		 	}	
		 }
		 t=DijkstraFindAvailableShortest(n);
 	}
}
inline int Graph::DijkstraFindAvailableShortest(int n){
	//返回未确定集合中源点最近的可到达的点,没有时返回-1 
	int t=-1,minn=Max;
	for(int i=1;i<=Vlen;i++){
		if(VNode[i].color==-1&&VNode[i].d>0&&VNode[i].d<minn){
			minn=VNode[i].d;
			t=i;
		}
	}
	if(t!=-1)
		VNode[t].color=0;
	return t;
}
void Graph::Floyd(){
	int tempMatrix[VMax][VMax];//tempMatrix是很有必要的... 
	for(int i=1;i<=Vlen;i++){
		for(int j=1;j<=Vlen;j++){
			if(Matrix[i][j]==0&&i!=j){
				Matrix[i][j]=Max;
			}
		}
	}		
	memcpy(tempMatrix,Matrix,sizeof(int)*VMax*VMax);
	for(int k=1;k<=Vlen;k++){
		for(int i=1;i<=Vlen;i++){
			for(int j=1;j<=Vlen;j++){
				int temp=tempMatrix[i][k]+tempMatrix[k][j];
				if(temp<tempMatrix[i][j])
					Matrix[i][j]=temp;
			}
		}
		memcpy(tempMatrix,Matrix,sizeof(int)*VMax*VMax);
	}
}
inline void Graph::setnetworkMap(){
	memcpy(networkMap,Matrix,sizeof(Matrix));
}
void Graph::EdmondKarp(int start,int end){
	//最后得到的networkMap是残留网络, networkMap[i][j]表示点i到点j能通过多大
	//的流量,源点的列和或者汇点的行和代表整个网络的最大流 
	int p[Vlen+10],flag[Vlen+10];
	while(EKPathFindBFS(networkMap,p,flag,start,end)){
		int minn = Max,u=end;
		while(p[u]!=-1){
			minn = (minn<networkMap[p[u]][u])?minn:networkMap[p[u]][u];
			u=p[u];
		}
		u=end;
		while(p[u]!=-1){
			networkMap[p[u]][u]-=minn;
			networkMap[u][p[u]]+=minn;
			u=p[u];
		}
	}
	int sum=0;
	for(int i=1;i<=Vlen;i++)sum+=networkMap[i][1];
	cout<<"the maximun stream is "<<sum<<endl;
}
bool Graph::EKPathFindBFS(int map[VMax][VMax],int *p,int *flag,int start,int end){
	memset(p+1,-1,sizeof(int)*Vlen);
	memset(flag+1,0,sizeof(int)*Vlen);
	queue <int>que;
	que.push(start);
	flag[start]=1;
	while(!que.empty()){
		int tempStrat = que.front();
		if(tempStrat==end)return true;
		que.pop();
		for(int i=1;i<=Vlen;i++){
			if(map[tempStrat][i]&&!flag[i]){
				flag[i]=1;
				p[i]=tempStrat;
				que.push(i);
			}
		}
	}
	return false;
}
void Graph::setMatchMap(){
	for(int i=1;i<=Vlen;i++)
	for(int j=1;j<=Vlen;j++){
		if(Matrix[i][j]!=Max)
			matchMap[i+1][j+1]=Matrix[i][j];
		else
			matchMap[i+1][j+1]=0;
	}
}
void Graph::binaryMaximumMatch(){
	
}
void Graph::show(){
	cout<<"Vlen:"<<Vlen<<endl;
	cout<<"Elen:"<<Elen<<endl;
	//cout<<"IMatirix:"<<endl;
//	for(int i=1;i<=Vlen;i++){
//		for(int j=1;j<=Vlen;j++)
//			cout<<IMatrix[i][j]<<" ";
//		cout<<endl;
//	}
//	cout<<endl;
	cout<<"network:"<<endl;
	for(int i=1;i<=Vlen;i++){
		for(int j=1;j<=Vlen;j++)
			cout<<networkMap[i][j]<<" ";
		cout<<endl;
	}
//	cout<<endl;
//	cout<<"IENode:"<<endl;
//	for(int i=1;i<=Elen;i++){
//		IENode[i].show();
//	}
//	cout<<endl;
//	cout<<"ENode:"<<endl;
//	for(int i=1;i<=Elen;i++){
//		ENode[i].show();
//	}
//	cout<<endl;
//for(int i=1;i<=Vlen;i++)
//cout<<VNode[i].d<<" ";
//cout<<endl;
//for(int i=1;i<=Vlen;i++)
//cout<<VNode[i].parent<<" ";
//cout<<endl;
}
int main(){	
	int len;
	cin>>len;
	Graph a;
	a.inputIENode(len);
	a.IENode2Matrix();
	a.setnetworkMap();
	a.EdmondKarp(1,6);
	a.show();
	return 0;
}