/*
	座位表随机生成系统的开源代码，版本号1.7.1

	编译与运行：本代码遵循C++17标准，只能使用Visual Studio 2019编译运行，Dev-C++ 5.11由于使用C++11标准，无法正常编译此代码
	查看与编辑：可使用任何文本编辑器查看和编辑
	由于特殊原因，开发人员在开源代码中进行了极其微小的修改，以免发生与原版混淆的情况
	所有以开源代码编译生成的程序，均不可用于正规使用
	对于代码有修改意见可以提给开发人员

	作者：w2563070231@outlook.com
*/

//#include<bits/stdc++.h>
//#include<ifstream>
//#include<oftstream>
//#include<stdio.h>
//#include<string.h>
#include <iostream>
#include <fstream>
#include "windows.h"
#include <cstdio>
#include <random>
#include <time.h>
#include <cstring>


using namespace std;

FILE* fin, * fout1/*fout2,*fout3,*fout4,*fout5,*fout6,*fout7  注销无用文件指针*/;

int coun;

std::random_device rd;     //从随机库中取得随机数种子
std::mt19937_64 eng(rd()); //使用64位随机数生引擎
						   //取得无符号整型随机数
std::uniform_int_distribution<unsigned long long> distr(1, 600);//取得1~600间随机整数

struct stu {
	int bh;	//学生编号，好像没什么用
	char name[7];	//学生姓名
	int fl;	//flag变量，记录是否使用，在后续生成中起作用
}stud[54];	//学生类数组

struct stab {
	char stname[7];
}table[9][8];//座位表

//ifstream ou1;
//ou1.open("sss.txt",ios_base::in);
//inf.open("d://读入文件.TXT");
//无用的测试文件流代码

inline int ran() {
	int n = distr(eng);

	//	for(int i=1;i<=n;++i)
	//	{
	//		int mp=distr(eng);
	//	}
	//	n=distr(eng);
	//	return abs(distr(eng)%53);
	//曾经使用过的随机数生成代码

	srand(time(0));	//获得计算机时间随机种子
	int rans = rand() + distr(eng);	//生成随机数
	//	rans*=19260817;
	rans = abs(rans / n);	//取绝对商
	//	cout<<n<<' ';
	return rans % 53 + 1;	//余数加1，获得随机编号
}//随机数函数

inline int topic() {
	char pd;
	cout << "          欢迎使用";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);//设置文本颜色
	cout << "座位表随机生成器开源版V1.7.1" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << "以下为注意事项：" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "1.此程序目前只适用于广华中学高三（2）班（53人）座位表生成，更多功能等待后续更新。" << endl;
	cout << "2.请确保在此运行程序（.exe）同一目录内有文件“读入文件.TXT”，并且已将学生编号与姓名写入此文本文档。" << endl;
	cout << "3.程序理论上会在同一目录内生成7个“座位表i.txt”的文件（后续升级支持），选取合适后复制粘贴入Excel或WPS表格即可。建议生成  一个复制一个，可以进行比较。" << endl;
	cout << "4.程序理论上输出一个座位表的时间约为5ms(与使用程序计算机时间有一定关系，可能会出现超过10秒的情况)，占用计算机内存1004KB。" << endl << "  测试平台：Intel(R) Core(TM) i7-8565U CPU @ 1.80GHz 1.99GHz 动态加速频率：4.6GHz" << endl << "  安装运行内存：8GB " << endl << "  Windows版本：Windows 10 家庭中文版 2004 19041.329" << endl;
	cout << "5.如有bug，请及时联系开发人员。" << endl;
	cout << "=====================================================";
	cout << "\nv1.7.1更新内容：\n(1)优化随机座位表生成与输出速度\n(2)采用全新开发与编译方式，内存占用减小\n(3)解决v1.7.0较高概率超时的情况" << endl;
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
		fscanf(fin, "%d %s", &stud[i].bh, &stud[i].name, 10);	//这里是C++17标准的文件输入格式
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
			//			unsigned int ee;无用变量，予以注销
			int ranst = ran();
			while (stud[ranst].fl == 1/*所取的人已经在先前使用过*/) {
				//				unsigned int seed;无用变量，予以注销
				ranst = ran();//再取一个随机值
				//				printf("%d ",ranst);无用变量，予以注销
			}//直到未使用，跳出while语句
			strncpy_s(table[i][j].stname, stud[ranst].name, 6);	//拷贝学生姓名到座位表(strncpy_s为C++17标准规定)
			stud[ranst].fl = 1;	//已使用，置flag变量f1为1
			count++;	//计数

			if (count == 53) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				printf("制作完成！！\n");
				return;
			}	//当制作完成后，输出“制作完成！！”，之后退出tablec()函数
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		printf("已完成：%d/8 ", i);	//本来用于输出进度，但由于版本更新后速度太快，没有什么感觉
	}

}//制作座位表

void print() {	//在控制台打印座位表
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
}	//未使用函数

int demain() {
	fin = fopen("读入文件.TXT", "r");
	fout1 = fopen("座位表1.txt", "w");
	int fd;
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
	return 0;
}	//未使用函数

int main()	//主函数/主程序
{
	fin = fopen("读入文件.TXT", "r");
	fout1 = fopen("座位表1.txt", "w");

	if (topic() == 0) return 0;
	init();

	int fd;	//未使用变量，本用于记录ask()函数返回值，因为ask()未使用，此变量也未使用，编译时可能会警告，但不会报错

	clock_t start, end;	//定义时间变量
	start = clock();	//记录开始运行时间

	tablec();	//主要运行部分
	print();
	fprint();

	end = clock();	//记录中止运行时间
	double runtime = (double)((double)end - (double)start) / CLOCKS_PER_SEC;	//计算用时
	cout << "\n运行时间为：" << runtime << "s" << endl;	//输出用时

	system("pause");	//系统暂停，方便查看

	return 0;

}
