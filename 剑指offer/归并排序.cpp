#include<iostream>
using namespace std;

template<class T>
void Merge(T A[], T TmpArray[], int Lpos, int Rpos, int RightEnd){
	int LeftEnd = Rpos-1, TmpPos=Lpos, NumElements=RightEnd-Lpos+1;
	while(Lpos <= LeftEnd && Rpos <= RightEnd)
		if(A[Lpos] <= A[Rpos])
			TmpArray[TmpPos++] = A[Lpos++];
		else
			TmpArray[TmpPos++] = A[Rpos++];
			
	while(Lpos <= LeftEnd)
		TmpArray[TmpPos++] = A[Lpos++];
	while(Rpos <= RightEnd)
		TmpArray[TmpPos++] = A[Rpos++];
		
	for(int i=0;i<NumElements;i++,RightEnd--)
		A[RightEnd] = TmpArray[RightEnd];
}
template <class T>
void MSort(T A[], T TmpArray[], int Left, int Right){
	int Mid = Left + (Right-Left)/2;
	if(Left<Right){
		MSort(A, TmpArray, Left, Mid);
		MSort(A, TmpArray, Mid+1, Right);
		Merge(A, TmpArray, Left, Mid+1, Right);
	}
}
template<class T>
void Mergesort(T A[], int N){
	T* TmpArray = new T[N];
	if(TmpArray != NULL){
		MSort(A, TmpArray, 0, N-1);
		delete []TmpArray;
	}
	else{
		cout<<"No space"<<endl;
		return;
	}
}


int main(){
	
	return 0;
} 