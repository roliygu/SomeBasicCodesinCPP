#include<iostream>
using namespace std;

void transF(char *old){
	int len=strlen(old),numSpace=0,newLen;
	for(int i=0;i<len;i++)
		numSpace += (old[i]==' ')?1:0;
	newLen+=(numSpace*2);
	for(int i=len;i>=0;i--){
		if(old[i]!=' ')
			old[i+2*numSpace]=old[i];
		else{
			numSpace--;
			int index = 2*numSpace+i;
			old[index]='%';
			old[index+1]='2';
			old[index+2]='0';
		}
	}
}

int main(){
	char p[20]="Wearehappy";
	transF(p);
	cout<<p<<endl;
	
	
	return 0;
}