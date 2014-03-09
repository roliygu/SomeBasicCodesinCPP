#include<iostream>
#include<string>
using namespace std;

class Student{
	private:
		string name,ID;
		int gra[4];
	public:
		Student(string T);
		void show();
};
Student::Student(string T){
	int n=0,gr=0,c=1;
	for(int i=T.size()-1;i>=0;i--){
		if(T[i]==','){
			gra[3-n]=gr;
			n++;
			gr=0;
			c=1;
		}
		else{
			gr+=c*(T[i]-'0');
			c*=10;
		}
		if(n>3)break;
	}
}
void Student::show(){
	for(int i=0;i<=3;i++)cout<<gra[i]<<" ";
}
int main(){
	string a="Tom,18,7817,80,80,90,70";
	Student b(a);
	b.show();
	return 0;
}
