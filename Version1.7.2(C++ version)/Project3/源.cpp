//#include<bits/stdc++.h>
#include <fstream>
//#include<ifstream>
//#include<oftstream>
//#include<stdio.h>
//#include<string.h>
#include <iostream>
#include "windows.h"
#include <cstdio>
#include <random>
#include <time.h>
#include <cstring>

using namespace std;

FILE* fin, * fout1/*fout2,*fout3,*fout4,*fout5,*fout6,*fout7*/;

int coun;

std::random_device rd;     //Get a random seed from the OS entropy device, or whatever
std::mt19937_64 eng(rd()); //Use the 64-bit Mersenne Twister 19937 generator
								//and seed it with entropy.

	//Define the distribution, by default it goes from 0 to MAX(unsigned long long)
	//or what have you.
std::uniform_int_distribution<unsigned long long> distr(1, 600);//取得1~600间随机整数

struct stu {
	int bh;
	char name[7];
	int fl;
}stud[54];//学生 

struct stab {
	char stname[7];
}table[9][8];//座位表 

//ifstream ou1;
//ou1.open("sss.txt",ios_base::in);
//inf.open("d://读入文件.TXT");

inline int ran() {
	int n = distr(eng);
	//	for(int i=1;i<=n;++i)
	//	{
	//		int mp=distr(eng);
	//	}
	//	n=distr(eng);
	//	return abs(distr(eng)%53);
	srand(time(0));
	int rans = rand() + distr(eng);
	//	rans*=19260817;
	rans = abs(rans / n);
	//	cout<<n<<' ';
	return rans % 53 + 1;
}//随机数函数 

inline int topic() {
	char pd;
	cout << "          欢迎使用";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//设置红色
	cout << "座位表随机生成器专业版V1.7.1" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << "以下为注意事项：" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "1.此程序仅限班委使用。" << endl;
	cout << "2.此程序目前只适用于广华中学高三（2）班（53人）座位表生成，更多功能等待后续更新。" << endl;
	cout << "3.请确保在此运行程序（.exe）同一目录内有文件“读入文件.TXT”，并且已将学生编号与姓名写入此文本文档。" << endl;
	cout << "4.本程序旨在随机生成座位表，不会按照任何人的意愿进行概率修改。唯一修改权只限于生成后，由班委调整。" << endl;
	cout << "5.程序理论上会在同一目录内生成7个“座位表i.txt”的文件（后续升级支持），选取合适后复制粘贴入Excel或WPS表格即可。建议生成  一个复制一个，可以进行比较。" << endl;
	cout << "6.程序理论上输出一个座位表的时间约为5ms(与使用程序计算机时间有一定关系，可能会出现超过10秒的情况)，占用计算机内存1004KB。" << endl << "  测试平台：Intel(R) Core(TM) i7-8565U CPU @ 1.80GHz 1.99GHz 动态加速频率：4.6GHz" << endl << "  安装运行内存：8GB " << endl << "  Windows版本：Windows 10 家庭中文版 2004 19041.329" << endl;
	cout << "7.如有bug，请及时联系开发人员。" << endl;
	cout << "=====================================================";
	cout << "\nv1.7.1b2更新内容：\n(1)优化随机座位表生成与输出速度\n(2)采用全新开发与编译方式，内存占用减小\n(3)解决v1.7.0较高概率超时的情况\n(4)解决输入其他字符无法退出的问题（新增）" << endl;
	cout << "-----------------------------------------------------";
	cout << "\nv2.0版本预告：\n(1)更换底层代码，使运行更加高效\n(2)新增Java与Python两种编写模式，提供优秀的跨平台体验\n(3)摆脱控制台的束缚，拥有更人性化的用户操作界面" << endl;
	cout << "=====================================================";
	cout << "\n如果已经确认无误，请输入“y/Y”并按下“Enter”开始，否则输入其他字符并按下“Enter”退出。" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	pd = getchar();
	if (pd == 'y' || pd == 'Y') return 1;
	else	return 0;
}//注意事项 

inline void init() {
	for (int i = 1; i <= 53; ++i)
	{
		fscanf_s(fin, "%d %s", &stud[i].bh, &stud[i].name,10);
		stud[i].fl = 0;
	}
	//	table[8][5].stname=table[8][6].stname=table[8][7].stname;
}//初始化与读入 

inline void tablec() {
	int count = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "正 ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "在 ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << "生 ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "成";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "......" << endl;
	for (int i = 1; i <= 8; ++i)
	{
		for (int j = 1; j <= 7; ++j)
		{
			//			unsigned int ee;
			int ranst = ran();
			while (stud[ranst].fl == 1) {
				//				unsigned int seed;
				ranst = ran();
				//				printf("%d ",ranst);
			}
			strncpy_s(table[i][j].stname, stud[ranst].name, 6);
			stud[ranst].fl = 1;
			count++;

			if (count == 53) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				printf("制作完成！！\n");
				return;
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		printf("已完成：%d/8 ", i);
	}

}//制作座位表

void print() {	//在控制台打印座位表
	//	(int i=1;i<=53;i++)
	//	{for
	//		if(stud[i].fl==0)
	//		{
	//			strncpy(table[8][4].stname,stud[i].name,6);
	//		}
	//	}
	//	int num=0;
	printf("\t\t\t\t讲  台\n");
	for (int i = 1; i <= 8; ++i)
	{
		for (int j = 1; j <= 7; ++j)
		{
			if (j == 2 || j == 5)
			{
				printf("%s\t\t", table[i][j].stname);
			}
			else printf("%s\t", table[i][j].stname);

		}
		printf("\n");
	}
}

void fprint() {		//在文件里打印座位表
	//	(int i=1;i<=53;i++)
	//	{for
	//		if(stud[i].fl==0)
	//		{
	//			strncpy(table[8][4].stname,stud[i].name,6);
	//		}
	//	}
	//	int num=0;
	fprintf(fout1, "\t\t\t\t讲  台\n");
	for (int i = 1; i <= 8; ++i)
	{
		for (int j = 1; j <= 7; ++j)
		{
			if (j == 2 || j == 5)
			{
				fprintf(fout1, "%s\t\t", table[i][j].stname);
			}
			else fprintf(fout1, "%s\t", table[i][j].stname);

		}
		fprintf(fout1, "\n");
	}
}

inline int ask() {
	cout << endl << endl;
	cout << "是否满意？（输入“y”代表“满意”，“n”表示不满意，并按下Enter）" << endl;
	char as = getchar();
	if (as == 'y') return 1;
	else return 0;
}

int demain() {
	fin = fopen("读入文件.TXT", "r");
	fout1 = fopen("座位表1.txt", "w");
	//if (topic() == 0) return 0;
	//init();
	int fd;
	//do {
	tablec();
	print();
	fprint();
	fd = ask();
	system("pause");
	if (fd == 1) {
		return 0;
	}
	else
	{
		demain();
	}
}
//void std_v1()
//{
//	int number=53;
//	for(int i=1;i<=8)
//}
int main()
{

	fin = fopen("读入文件.TXT", "r");
	fout1 = fopen("座位表1.txt", "w");
	//	cout<<ran();
	//	int sb=ran();
	//	int sbb=sb;
	//	cout<<sbb<<' ';
	//	while(sb==sbb)
	//	{
	//		sb=ran();
	//	}
	//	cout<<sb;
	//	for(int i=1;i<=10;++i)
	//	{
	//		cout<<ran()<<endl;
	//		cout<<rand()<<endl;
	//	}
	if (topic() == 0) return 0;
	else {
		init();
		int fd;
		//do {
		clock_t start, end;
		start = clock();
		tablec();
		print();
		fprint();
		end = clock();
		double runtime = (double)((double)end - (double)start) / CLOCKS_PER_SEC;
		cout << "\n运行时间为：" << runtime << "s" << endl;
		//fd = ask();
		system("pause");
		//if (fd == 1) {
		//	return 0;
	//	}
		//else
		//{
	//		demain();
	//	}
		return 0;
	}
	//} while (fd == 0);
	//	main(); 
	//	fout2=fopen("座位表2.txt","w");
	//	fout3=fopen("座位表3.txt","w");
	//	fout4=fopen("座位表4.txt","w");
	//	fout5=fopen("座位表5.txt","w");
	//	fout6=fopen("座位表6.txt","w");
	//	fout7=fopen("座位表7.txt","w");
	
}
