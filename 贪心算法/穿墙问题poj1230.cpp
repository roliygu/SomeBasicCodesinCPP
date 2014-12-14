//ԭ���������,������ǽ�պ�����һ��ǽ����Ϊ��Ȼ������,������������Ϊ��һ��ǽ 
//����ÿ��ǽ�ı�����ʹ��i�����Ǽ򵥵�0��1�Ļ�,�Ϳ���һ���̶Ƚ�����������
//ȴ�����ܽ��[1,4]��[2,3]��������ǽ������ 
#include<iostream>
#include<algorithm>
using namespace std;
class oneWall{
	public:
		int x,y,len;
};
class Wall{
	public:
		int W[105][105],max_x,max_y,k,sum;
		Wall(int nt,int kt);
		void remove(int t);
		inline int calculate(int x,int t);
		inline void rem(int x,int t);
		void show();
};
bool cmp(oneWall A,oneWall B){
	return A.len>B.len;
}
Wall::Wall(int nt,int kt){
	memset(W,0,sizeof(W));
	max_x=nt;
	max_y=nt;
	k=kt;
	sum=0;
	int x1,x2,y1,y2;
	for(int i=1;i<=nt;i++){
		cin>>x1>>y1>>x2>>y2;
		if(x2>max_x)max_x=x2;
		if(x1>max_x)max_x=x1;
		if(y1>max_y)max_y=y1;
		for(int j=x1;j<=x2;j++){
			W[y1][j]=1;
		}
	}
}
inline int Wall::calculate(int x,int t){
	//�����x��,��t�п�ʼǽ�ĳ���
	int  sum=0;
	for(int i=t;W[x][i]==1;i++)
		sum++;
	return sum;
}
inline void Wall::rem(int x,int t){
	//ȥ����x�д�t�п�ʼ��ǽ
	for(int i=t;W[x][i]==1;i++)
		W[x][i]=0;
}
void Wall::remove(int t){
	//ɨ�赽��t��ʱ 
	oneWall T[110];
	int tempI=0;
	for(int i=1;i<=max_x;i++){
		if(W[i][t]==1){
			int temp=calculate(i,t);
			T[tempI].x=i;
			T[tempI].y=t;
			T[tempI].len=temp;
			tempI++;
		}
	}
	int movenum=tempI-k;
	if(movenum>=0)
		sum+=movenum;
	while(movenum>0){
		rem(T[movenum-1].x,T[movenum-1].y);
		movenum--;
	}
}
void Wall::show(){
	for(int i=0;i<=max_x;i++){
		for(int j=0;j<=max_x;j++)
			cout<<W[i][j]<<" ";
		cout<<endl;
	}
}
int main(){
	int testnum,x,y;
	cin>>testnum;
	for(int i=1;i<=testnum;i++){
		cin>>x>>y;
		Wall A(x,y);
		for(int j=1;j<=A.max_x;j++){
			A.remove(j);
		}
		cout<<A.sum<<endl;;
	}
} 