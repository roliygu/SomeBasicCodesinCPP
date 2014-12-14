#include<iostream>
using namespace std;
const int Max=1024;
class MaxSum{
	private:
		int sum[Max],len,maxEndIndex,maxStartIndex,maxsum;
	public:	
		MaxSum(int *A,int L);
		void setup();
		void show();
};
MaxSum::MaxSum(int *A,int L){
	//AԪ�ش�0��ʼ 
	len=L;
	maxsum=0;
	for(int i=1;i<=L;i++)
		sum[i]=A[i-1];
}
void MaxSum::setup(){
	int tempsum=0;
	for(int i=1;i<=len;i++){
		if(tempsum>0)
			tempsum+=sum[i];
		else
			tempsum=sum[i];
		if(tempsum>maxsum){
			maxsum=tempsum;
			maxEndIndex=i;
		}	
	}
	int tempmax=maxsum;
	for(int i=maxEndIndex;i>=1;i--){
		if(tempmax-sum[i]==0)
			maxStartIndex=i;
		else
			tempmax-=sum[i];
	}
}
void MaxSum::show(){
	for(int i=1;i<=len;i++)
	cout<<sum[i]<<" ";
	cout<<endl;
	cout<<"the sum of ["<<maxStartIndex<<','<<maxEndIndex<<"] "<<maxsum<<" is the maximum."<<endl;
}
int main(){
	int A[10]={-2,11,-4,13,-5,-2};
	MaxSum B(A,6);
	B.setup();
	B.show();
	return 0;
}