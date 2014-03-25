//queue 用front获得队首元素,然后top弹出,才能获得第二个"队首"
//引用做函数参数,需在函数外先对其赋初值,然后函数修改才有效
//vector不是数据类型,所以没有 vector a[10]这样表示10个vector组成数组的方式,只能写作
//vector <T> a[10] 
//遍历vector的所用元素,使用t.begin(),t.end()和迭代器 
//sort(start,end,cmp)cmp{return a<b;}时结果是升序 


#include<iostream>
#include<list>
#include<set>
#include<queue>
#include<algorithm>
using namespace std;

//EMax是用邻接表或边集表示的最大边数
//VMax是用邻接矩阵表示的最大节点数
//Max是可能出现的最大权值
const int EMax=1024;
const int VMax=200;
const int Max=999999;
int A[EMax][4];
//Set是当前实现的一个简陋的"并查集",暂时还不打算用其他数据结构来优化
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

//GNode是邻接表中的节点.存储的此条"有向边"的终点和权值
class GNode{
	public:
		int end,weight;
};
//Node是一个抽象意义上的点,具体意思根据不同算法来理解
class Node{
	public:
		int color,d,parent;
		Node(){
			/*
				Dijkstra算法中:
					color=-1表示还没有对该点的所有关联点"松弛"刷新(参见算法导论)
					color=0表示已经刷新了其所有关联点;也就是<算法导论>中集合S和Q
					d是在当前状态下,距离源点n的距离
					parent是当前造成距离d的路径中的上一个节点
			*/
			/*
				搜索中,color=-1表示当前未知的点,color=0表示当前正在处
					理的点,color=1表示处理完成的点 
			*/
			color=-1;
			d=-1;
			parent=-1;
		}
};
bool operator <(Node a,Node b){
	return a.d<b.d;
}
//Edge是边.存储了边的起点,终点和权值
class Edge{
	public:
		int a,b,w;
		bool select;
		void show(){
			cout<<'('<<a<<' '<<b<<' '<<w<<')'<<endl;
		};
};
//重点,图
class Graph{
	private:
		/*
			direction = 0 表示无向图,=1表示有向图.默认构造的是有向图
			ENode,Matrix和map分别是图的三种表示方法:边集,邻接矩阵和邻接表
			IENode,IMatrix是用户输入边集和邻接矩阵暂存的容器.部分算法需要
			直接修改邻接矩阵或者邻接表时修改的就是这两个.以达到隔离真正的
			邻接矩阵和邻接表的效果.
			networkMap是网络流算法需要的邻接矩阵的一个拷贝
			matchMap是二分图匹配算法需要的邻接矩阵的一个拷贝(相关算法未完成)
			V是广度优先搜索暂存节点的队列
		*/
		int Elen,Vlen;
		bool direction;
		Node VNode[VMax];
		Edge IENode[EMax];
		Edge ENode[EMax];	
		list <GNode> map[VMax];	
		int IMatrix[VMax][VMax];	
		int Matrix[VMax][VMax];
		int networkMap[VMax][VMax];	
		int matchMap[VMax][VMax];
		queue <int> V;
	public:	
		/*
			inputIMatrix()和inputIENode()如前面所说,是类与用户交互的接口
			inputIMatrix的参数是邻接矩阵的大小,也就是节点数
			inputIENode的参数是边的条数,第二个默认参数是有向or无向图的标记
				通过输入边集来构图时,并不知道节点的个数.这里用到了calVNodeNum()
				其第一个参数就是IENode,第二个参数边数
			IMatrix2Matrix(),IMatrix2ENode(),IENode2ENode()和IENode2Matrix()
				如名字所示,是通过IENode或IMatrix构造真正的ENode和Matrix的函数
			setup() 通过边集构造邻接表
			BFS()基于邻接表和队列V的广搜
			DFS()基于邻接表的深搜
			topogySort() 基于邻接矩阵的拓扑排序.要求有向无环图.
			Kruskal()基于边集的最小生成树算法
			Dijkstra() 单源最短路径算法;不支持负权;最后距离源点n的最短距离保存在VNode中
				DEmpty()和DMin() Dijkstra()需要的子函数.具体参考<算法导论>
			Floyd() 基于邻接矩阵,支持负权,求任意两点最短路径算法
		*/
		inline void inputIMatrix(int len);		
		inline void inputIENode(int len,int dic);
		inline int calVNodeNum(Edge A[EMax],int len);
		inline void IMatrix2Matrix();
		inline void IMatrix2ENode();
		inline void IENode2ENode();
		inline void IENode2Matrix();
		void setup();
		void BFS();
		void DFS();
		void SubDFS(int i);
		void topogySort();
		void Kruskal();
		void Dijkstra(int n);
		inline bool DEmpty();
		inline int DMin();
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
inline int Graph::calVNodeNum(Edge A[EMax],int len){
	set<int> V;
	for(int i=1;i<=len;i++){
		V.insert(A[i].a);
		V.insert(A[i].b);
	}
	return V.size();
}
inline void Graph::inputIMatrix(int len){
	//len表示点数
	Vlen=len;
	for(int i=1;i<=len;i++)
		for(int j=1;j<=len;j++){
			cin>>IMatrix[i][j];	
		}
}
inline void Graph::inputIENode(int len,int dic=1){
	//len表示边的条数
	Elen=len;
	direction = dic;
	int maxx=-1;
	for(int i=1;i<=len;i++){
		cin>>IENode[i].a>>IENode[i].b>>IENode[i].w;
		IENode[i].select=false;
	}
	Vlen=calVNodeNum(IENode,Elen);
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
	if(direction==0)
		for(int i=1;i<=Elen;i++)
			Matrix[IENode[i].b][IENode[i].a]=IENode[i].w;
	for(int i=1;i<=Vlen;i++)Matrix[i][i]=0;
}
void Graph::setup(){
	for(int i=1;i<=Elen;i++){
		int start = IENode[i].a;
		GNode e;
		e.end=IENode[i].b;
		e.weight=IENode[i].w;
		map[start].push_front(e);
	}
}
void Graph::BFS(){
	for(int i=1;i<=Vlen;i++)VNode[i].color=-1;
	V.push(1);
	while(V.size()!=0){
		int i = V.front();
		V.pop();
		cout<<i<<" ";
		for(list <GNode>::iterator j=map[i].begin();j!=map[i].end();advance(j,1)){
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
	for(list <GNode>::iterator j=map[i].begin();j!=map[i].end();advance(j,1)){
		if(VNode[(*j).end].color==-1)
			SubDFS((*j).end);
		VNode[(*j).end].color=1;
	}
}
void Graph::topogySort(){
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
inline bool Graph::DEmpty(){
	for(int i=1;i<=Vlen;i++)
		if(VNode[i].color==-1)
			return false;
	return true;
}
inline int Graph::DMin(){
	int minIndex = Vlen+5;
	int minn = Max;
	for(int i=1;i<=Vlen;i++)
		if(VNode[i].color==-1&&VNode[i].d<minn){
			minn = VNode[i].d;
			minIndex = i;
		}
	return minIndex;
}
void Graph::Dijkstra(int n){
	for(int i=1;i<=Vlen;i++)
		VNode[i].d = Max;
	VNode[n].d=0;
	while(!DEmpty()){
		int u = DMin();
		VNode[u].color = 0;
		for(list<GNode>::iterator j=map[u].begin();j!=map[u].end();advance(j,1)){
			int point = (*j).end;
			if(VNode[point].d>VNode[u].d+(*j).weight){
				VNode[point].d = VNode[u].d+(*j).weight;
				VNode[point].parent = u;
			}
		}
	}
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
//	cout<<"Vlen:"<<Vlen<<endl;
//	cout<<"Elen:"<<Elen<<endl;
//	cout<<"Matirix:"<<endl;
//	for(int i=1;i<=Vlen;i++){
//		for(int j=1;j<=Vlen;j++)
//			cout<<Matrix[i][j]<<" ";
//		cout<<endl;
//	}
//	cout<<endl;
//	cout<<"IMatirix:"<<endl;
//	for(int i=1;i<=Vlen;i++){
//		for(int j=1;j<=Vlen;j++)
//			cout<<IMatrix[i][j]<<" ";
//		cout<<endl;
//	}
//	cout<<endl;
//	cout<<"network:"<<endl;
//	for(int i=1;i<=Vlen;i++){
//		for(int j=1;j<=Vlen;j++)
//			cout<<networkMap[i][j]<<" ";
//		cout<<endl;
//	}
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
	for(int i=1;i<=Vlen;i++)
		cout<<VNode[i].d<<" ";
	cout<<endl;
//for(int i=1;i<=Vlen;i++)
//cout<<VNode[i].parent<<" ";
//cout<<endl;
//	cout<<"map:"<<endl;
//	for(int i=1;i<=Vlen;i++){
//		cout<<i<<": ";
//		for(list<GNode>::iterator j=map[i].begin();j!=map[i].end();advance(j,1))
//			cout<<"->"<<(*j).end<<" "<<(*j).weight<<" ";
//		cout<<endl;
//	}
}
int main(){	
	int len;
	cin>>len;
	Graph a;
	a.inputIENode(len);
	a.IENode2ENode();
	a.setup();
	a.Dijkstra(1);
	a.show();
	return 0;
}