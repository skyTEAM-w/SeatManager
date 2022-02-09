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
		cout<<"欢迎"<<UserName<<"回来"<<endl;
	}
	else cout<<"用户名或密码错误"<<endl;
}

void UIinit(){
	cout<<"欢迎使用本系统"<<endl;
	cout<<"请输入用户名与密码"<<endl;
	cout<<"用户名：";
	char Name[20];
	cin>>Name;
//	cout<<endl;
	cout<<"密码：";
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
