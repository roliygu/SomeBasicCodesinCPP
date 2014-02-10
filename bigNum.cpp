/*
keypoints:
	1.new函数返回的是指针
	2.string对象必须先确定大小(resize),才能用下标赋值
	3.内存刷新函数memset(*a, 0, sizeof(int)*maxn) 
*/ 

#include<iostream>
#include<string>
using namespace std;
#define maxn 1000
struct Mod;
class bigNum{
	private:
		string s;
		int number[maxn];
		int len;
		int flag;
		int Absolutevaluecompare(bigNum B);		
	public:
		void min(bigNum A, bigNum B);
		bigNum(string T);
		bigNum();
		bigNum AbsolutevalueAdd(bigNum B);
		bigNum AbsolutevalueMinus(bigNum B); 
		bigNum Add(bigNum B);
		bigNum Minus(bigNum B);
		void power(int t);
		bigNum mulbit(int t);
		bigNum Mul(bigNum B);
		bool equalzero();
		int compare(bigNum B);
		Mod Division(bigNum B);
		void StringtoNum();
		void NumtoString();
		void show();
};
struct Mod{
	bigNum quotient;
	bigNum remainder;
};
bigNum::bigNum(const string T){
	if(T[0]=='-'){
		flag = -1;
		s.assign(T, 1, T.size()-1);	
	}else{
		s = T;
		//这里没有特别区分是否为0,认为0属于正数	
		flag = 1;
	}	
	len = s.size();
	memset(number, 0, sizeof(int)*maxn);
	StringtoNum();
}
bigNum::bigNum(){
	flag = 1;
	memset(number, 0, sizeof(int)*maxn);
	s = "0"; 
	len = 1;
}
//bigNum::bigNum(bigNum B){
//	flag=B.flag;
//	s=B.s
//	len=B.len;
//	memcpy(number,B.number,sizeof(int)*maxn);
//}
void bigNum::min(bigNum A, bigNum B){
	//这里默认A比B值大,且A,B都为正
	int carrybit=0;
	len = A.len;
	int i = 0;
	for(;i<A.len;i++){
		A.number[i]-=carrybit;
		if((A.number[i]-B.number[i])<0){
			number[i] = A.number[i]-B.number[i]+10;
			carrybit = 1;
		}else{
			number[i] = A.number[i]-B.number[i];
			carrybit = 0;
		}
	} 
	if(number[len-1]==0)len--;
}
bigNum bigNum::AbsolutevalueMinus(bigNum B){
	int t = Absolutevaluecompare(B);
	bigNum C;
	if(t==0){
		C.len=1;
		C.s="0";
		C.flag=1;
	}else if(t==-1){
		C.min(B, *this);
		C.flag=-1;
		C.NumtoString();
	}else{
		C.min(*this, B);
		C.flag=1;
		C.NumtoString();
	}
	return C;
}
int bigNum::Absolutevaluecompare(bigNum B){
	//两个高精度数必须非负,大于返回1,小于返回-1,等于返回0 
	if(len!=B.len)
		return (len>B.len)?1:-1;
	else{
		for(int i=len-1;i>=0;--i){
			if(number[i]!=B.number[i])
				return (number[i]>B.number[i])?1:-1;
			else
				continue;
		}
		return 0;
	} 
}
int bigNum::compare(bigNum B){
	if(flag!=B.flag){
		return (flag>B.flag)?1:-1;
	}else if(flag==1){
		return Absolutevaluecompare(B);
	}else{
		return (-1)*Absolutevaluecompare(B);
	}
}
bigNum bigNum::AbsolutevalueAdd(bigNum B){
	bigNum C;
	int carrybit=0;
	int maxlen = (len>B.len)?len:B.len;
	for(int i=0;i<maxlen;i++){
		int temp = carrybit+number[i]+B.number[i];
		carrybit = temp/10;
		C.number[i] = (temp>9)?(temp%10):temp;
	}
	C.number[maxlen] = (carrybit!=0)?carrybit:0;
	C.len = (carrybit!=0)?maxlen+1:maxlen;
	C.flag = 1;
	C.NumtoString();
	return C;
}
void bigNum::StringtoNum(){
	for(int i=0;i<s.size();i++){
		number[s.size()-i-1] = s[i]-'0';
	}
}
void bigNum::NumtoString(){
	s.resize(len,'0');
	for(int i=0;i<len;i++){
		s[i] = number[len-i-1]+'0';
	}
}
bigNum bigNum::Add(bigNum B){
	int f = flag*B.flag;
	bigNum C;
	if(f>0){		
		C=AbsolutevalueAdd(B);
		C.flag=flag;
		return C;
	}else{
		C=AbsolutevalueMinus(B);
		int k = Absolutevaluecompare(B);
		if(k==0)
			C.flag=1;
		else if(k>0)
			C.flag=flag;
		else
			C.flag=B.flag;
		return C;
	}
}
bigNum bigNum::Minus(bigNum B){
	B.flag*=(-1);
	bigNum C;
	C=Add(B);
	return C;
}
void bigNum::power(int t){
	//使结果乘以10的t次方
	if(t>=0){
		for(int i=len-1;i>=0;i--)number[i+t]=number[i];
		for(int i=t-1;i>=0;i--)number[i]=0;
	}else{
		for(int i=0;i<=len+t;i++)number[i]=number[i-t];
	}
	len+=t;
	NumtoString();
}
bigNum bigNum::mulbit(int t){
	bigNum C;
	int carrybit=0;
	for(int i=0;i<=len;i++){
		int temp = number[i]*t;
		temp+=carrybit;
		C.number[i]=temp%10;
		carrybit=temp/10;
	}
	if(C.number[len]!=0)C.len=len+1;
	C.NumtoString();
	return C;
}
bigNum bigNum::Mul(bigNum B){
	bigNum C;
	for(int i=0;i<B.len;i++){
		bigNum D = mulbit(B.number[i]);
		D.power(i);
		C = C.AbsolutevalueAdd(D);
	}
	if(equalzero()||B.equalzero())
		C.flag = 1;
	else
		C.flag=flag*B.flag;
	return C;
}
Mod bigNum::Division(bigNum B){
	//这里应该再加一条判断B==0的异常 
	Mod temp;
	if(Absolutevaluecompare(B)==-1){
		temp.remainder = *this;
		bigNum *p = new bigNum("0");
		temp.quotient = *p;
	}else if(Absolutevaluecompare(B)==0){
		bigNum *p = new bigNum("1");
		bigNum *q = new bigNum("0");
		temp.quotient = *p;
		temp.remainder = *q;
	}else{
		//有些问题,例如正负情况不同时余数也要分情况解决 
	}
	temp.quotient.flag = flag*B.flag;
	return temp;
}
bool bigNum::equalzero(){
	if(len!=1)
		return false;
	else{
		if(number[0]!=0)
			return false;
		else
			return true;
	}
}
void bigNum::show(){
	if(flag==-1)
		cout<<"s:-"<<s<<endl;
	else 
		cout<<"s:"<<s<<endl;
	cout<<"len:"<<len<<endl;
	cout<<"flag:"<<flag<<endl;
	for(int i=0;i<len;i++)cout<<number[i];
}
int main(){
	string a = "998";
	string b = "999";
	bigNum *c = new bigNum(a);
	bigNum *d = new bigNum(b);
	Mod e = c->Division(*d);
	cout<<"商:"<<endl; 
	e.quotient.show();
	cout<<endl;
	cout<<"余:" <<endl;
	e.remainder.show();
	
	
//	string a[5]={"-2","-1","0","1","2"};
//	int b[5]={-2,-1,0,1,2};
//	for(int i=0;i<5;i++){
//		for(int j=0;j<5;j++){
//			bigNum *c = new bigNum(a[i]);
//			bigNum *d = new bigNum(a[j]);
//			cout<<b[i]-b[j]<<endl;
//		}
//	}
	return 0;
}