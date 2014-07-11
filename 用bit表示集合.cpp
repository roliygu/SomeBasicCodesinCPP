#include<iostream>
using namespace std;
bool set[10];
void show(int S){
	memset(set,0,sizeof(set));
	int i=0;
	while(S!=0){
		set[i++]=S%2;
		S=S/2;
	};
	for(int i=0;i<10;i++){
		if(set[i])
			cout<<i<<" ";
	}
	cout<<endl;
}
inline void addElem2Set(int Elem,int &S){
	S=(S|1<<Elem);
}
inline bool haveElemInSet(int Elem,int S){
	return S>>Elem&1;
}
inline void deleteElemFromSet(int Elem,int &S){
	S = S&~(1<<Elem);
}
inline void showAllKSubSetofSetU(int N,int k){
	int comb = (1<<k)-1;
	while(comb<1 << N){
		show(comb);
		int x = comb & -comb, y=comb+x;
		comb = ((comb & ~y)/x >>1)|y;
	};
}
inline void showAllKSubSetofSetS(int S,int k){
	int sub=S;
	do{
		show(sub);
		sub = (sub-1)&S;
	}while(sub!=S);
}
int main(){
//	int S = 11;
//	cout<<"the initial Set is : ";
//	show(S);
//	addElem2Set(3,S);
//	cout<<"the Set add (elem:3):  ";
//	show(S);
//	cout<<"have Elem: 3? "<<haveElemInSet(3,S)<<endl;
//	cout<<"have Elem: 5? "<<haveElemInSet(5,S)<<endl;
//	deleteElemFromSet(1,S);
//	cout<<"the Set delete (elem:1):  ";
//	show(S);
//	showAllKSubSetofSetU(5,3);
//	showAllKSubSetofSetS(S,2);
	return 0;
}