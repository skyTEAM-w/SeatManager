#include<iostream>
#include<cstdio>
#include<cstring>
#include<windows.h>
#include<stdlib.h>
using namespace std;

void Check(string UserName,string Pass){
    char bascalname[10]="admin";
    char bascalpass[10]="123";
	if(strcmp(UserName,bascalname)&&strcmp(Pass,bascalpass){
		cout<<"��ӭ"<<UserName<<"����"<<endl;
	}
	else cout<<"�û������������"<<endl;
}

void UIinit(){
	cout<<"��ӭʹ�ñ�ϵͳ"<<endl;
	cout<<"�������û���������"<<endl;
	cout<<"�û�����";
	char Name[20];
	cin>>Name;
//	cout<<endl;
	cout<<"���룺";
	char PassPort[20];
	PassPort;
//	cout<<endl;
	Check(Name,PassPort);
}

int main(){
	UIinit();
	system("SeatM(C++).exe")
	return 0;
}
