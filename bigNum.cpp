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
class bigNum{
	private:
		string s;
		int number[maxn];
		int len;
		int flag;
		int Absolutevaluecompare(bigNum B);
	public:
		bigNum(string T);
		bigNum();
		bigNum AbsolutevalueAdd(bigNum B);
		bigNum AbsolutevalueMinus(bigNum B); 
		int compare(bigNum B);
		void StringtoNum();
		void NumtoString();
		void show();
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
	s = ""; 
	len = 0;
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
void bigNum::show(){
	if(flag==-1)
		cout<<"s:-"<<s<<endl;
	else 
		cout<<"s:"<<s<<endl;
	cout<<"len:"<<len<<endl;
	for(int i=0;i<len;i++)cout<<number[i];
}
int main(){
	//string a = "-9998";
	//string b = "999888";
	//bigNum *c = new bigNum(a);
	//bigNum *d = new bigNum(b);
	//cout<<c->compare(*d)<<endl;
	string a[5]={"-2","-1","0","1","2"};
	int b[5]={-2,-1,0,1,2};
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			bigNum *c = new bigNum(a[i]);
			bigNum *d = new bigNum(a[j]);
			cout<<a[i]<<" "<<(c->compare(*d)==(intcompar(b[i], b[j])))<<" "<<a[j]<<endl;
		}
	}
	return 0;
}