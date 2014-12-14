#include<iostream>
using namespace std;

class CMyString{
	public:
		CMyString(char * pData = NULL);
		CMyString(const CMyString& str);
		~CMyString(void);
		CMyString& operator= (const CMyString& str);
	private:
		char* m_pData;
}

CMyString& CMyString::operator=(const CMyString& str){
	if(this != &str){
		delete []m_pData;
		m_pData = NULL;
		m_pData = new char[strlen(str.m_pData)+1];
		strcpy(m_pData, str.m_pData);
	}
	return *this;
}
CMyString& CMyString::operator=(const CMyString& str){
	if(this != &str){
		CMyString tem(str);
		char* temp = tem.m_pData;
		tem.m_pData = m_pData;
		m_pData = temp;	
	}
	return *this;
}
int main(){
	
	return 0;
} 