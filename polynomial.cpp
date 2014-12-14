#include<iostream>
#include<string>
using namespace std;
#define maxn 100
class Polynomial{
private:
    int coeficient[maxn];
    int len;
public:
    Polynomial(int *A, int len);
    Polynomial();
    Polynomial Add(Polynomial B);
    Polynomial Minus(Polynomial B);
    Polynomial Multip(Polynomial B);
    void Show();
};
Polynomial::Polynomial(int *A, int len){
    memcpy(coeficient, A, sizeof(int)*maxn);
    while(A[len-1]==0)len--;
    this->len = len;
}
Polynomial::Polynomial(){
    memset(coeficient, 0, sizeof(int)*maxn);
    len = 0;
}
Polynomial Polynomial::Add(Polynomial B){
	int number[maxn];
	memset(number, 0, sizeof(int)*maxn);
	int l=(len>=B.len)?len:B.len;
	for(int i=0;i<l;i++){
		number[i]=coeficient[i]+B.coeficient[i];
	}
	Polynomial *C =new Polynomial(number, l);
	return *C;
}
Polynomial Polynomial::Minus(Polynomial B){
	int number[maxn];
	memset(number, 0, sizeof(int)*maxn);
	int l=(len>=B.len)?len:B.len;
	for(int i=0;i<l;i++){
		number[i]=coeficient[i]-B.coeficient[i];
	}
	Polynomial *C =new Polynomial(number, l);
	return *C;
}
Polynomial Polynomial::Multip(Polynomial B){
	int number[maxn];
	memset(number, 0, sizeof(int)*maxn);
	int l = len+B.len;
	for(int i=0;i<len;i++){
		for(int j=0;j<B.len;j++){
			number[i+j]+=coeficient[i]*B.coeficient[j];
		}
	}
	Polynomial *C =new Polynomial(number, l);
	return *C;
}
void Polynomial::Show(){
    if(len==0){
    	cout<<0;
    	return;
    }
    if(coeficient[len-1]>0){
        if(coeficient[len-1]==1)
            cout<<"x^"<<len-1<<" ";
        else
            cout<<coeficient[len-1]<<"x^"<<len-1<<" ";
    }
    else{
        if(coeficient[len-1]==-1)
            cout<<"-x^"<<len-1<<" ";
        else
            cout<<coeficient[len-1]<<"x^"<<len-1<<" ";
    }
    for(int i=len-2; i>=2; i--){
        if(coeficient[i]!=0)
            if(coeficient[i]>0)
                if(coeficient[i]==1)
                    cout<<"+ x^"<<i<<" ";
                else
                    cout<<"+ "<<coeficient[i]<<"x^"<<i<<" ";
            else
            	if(coeficient[i]==-1)
            		cout<<"- x^"<<i<<" ";
           		else
           			cout<<"- "<<(-coeficient[i])<<"x^"<<i<<" ";
        else
        	continue;
    }
        if(coeficient[1]!=0)
            if(coeficient[1]>0)
                if(coeficient[1]==1)
                    cout<<"+ x ";
                else
                    cout<<"+ "<<coeficient[1]<<"x ";
            else
            	if(coeficient[1]==-1)
            		cout<<"- x ";
           		else
           			cout<<"- "<<(-coeficient[1])<<"x ";
		if(coeficient[0]!=0)
            if(coeficient[0]>0)
                cout<<"+ "<<coeficient[0];
            else
                cout<<"- "<<(-coeficient[0]);
    }
    int main()
    {
        int A[maxn]= {1,1,1,-1,0,1,0,0,0};
        int B[maxn]= {0,1,0,0,0,0,0,0,0};
        Polynomial *b=new Polynomial(A, 9);
        Polynomial *a=new Polynomial(B, 9);
        Polynomial c = a->Multip(*b);
        c.Show();
        return 0;
    }