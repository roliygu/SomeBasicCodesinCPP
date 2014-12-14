#include<iostream>
#include<stack>
using namespace std;

template <class T>
class CQueue{
	public:
		// CQueue(void);
		// ~CQueue(void);
		
		void appendTail(const T& node);
		T deleteHead();
	
	private:
		stack<T> stack1;
		stack<T> stack2;
};

template<class T> void CQueue<T>::appendTail(const T& node){
	stack1.push(node);
}
template<class T> T CQueue<T>::deleteHead(){
	if(stack1.size()+stack2.size()<=0){
		cout<<"error"<<endl;
		return ;
	}else{
		if(stack2.size()>0){
			T tem = stack2.top();
			stack2.pop();
			return tem;
		}else{
			while(stack1.size()!=0){
				T temp = stack1.top();
				stack2.push(temp);
				stack1.pop();
			}
			T tem = stack2.top();
			stack2.pop();
			return tem;
		}
	}
}
int main(){
	
	
	return 0;
}