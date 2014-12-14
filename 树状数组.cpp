#include<iostream>
using namespace std;
const int Max=99999;
int A[1024];
class TreeArray{
	private:
		int pre[Max],len;
		inline int lowb(int i);
	public:
		TreeArray(int L,int *A);
		void IndexAdd(int index,int delet);
		int getSum(int index);
};
inline int TreeArray::lowb(int i){
	return i&(-i);
}
TreeArray::TreeArray(int L,int *A){
	//A从1开始存数 
	len=L;
	memset(pre,0,sizeof(int)*len);
	for(int i=1;i<=len;i++)
		IndexAdd(i,A[i]);
}
void TreeArray::IndexAdd(int index,int delet){
	for(;index<=len;pre[index]+=delet,index+=lowb(index));
}
int TreeArray::getSum(int i){
	int sum=0;
	for(;i>0;sum+=pre[i],i-=lowb(i));
	return sum;
}
int main(){
	for(int i=1;i<=1000;i++)
		A[i]=i;
	TreeArray B(1000,A);
	cout<<B.getSum(999);
	return 0;
} 