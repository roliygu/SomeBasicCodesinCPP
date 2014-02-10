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
    void Show();
};
Polynomial::Polynomial(int *A, int len){
    memcpy(coeficient, A, sizeof(int)*maxn);
    this->len = len;
}
Polynomial::Polynomial(){
    memset(coeficient, 0, sizeof(int)*maxn);
    len = 0;
}
void Polynomial::Show(){
    while(coeficient[len-1]==0)len--;
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
        int A[maxn]= {0,5,-55,0,0,0,0,0,0};
        Polynomial *b=new Polynomial(A, 9);
        b->Show();
        return 0;
    }