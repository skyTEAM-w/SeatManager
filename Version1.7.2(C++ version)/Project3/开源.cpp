/*
	��λ���������ϵͳ�Ŀ�Դ���룬�汾��1.7.1

	���������У���������ѭC++17��׼��ֻ��ʹ��Visual Studio 2019�������У�Dev-C++ 5.11����ʹ��C++11��׼���޷���������˴���
	�鿴��༭����ʹ���κ��ı��༭���鿴�ͱ༭
	��������ԭ�򣬿�����Ա�ڿ�Դ�����н����˼���΢С���޸ģ����ⷢ����ԭ����������
	�����Կ�Դ����������ɵĳ��򣬾�������������ʹ��
	���ڴ������޸�����������������Ա

	���ߣ�w2563070231@outlook.com
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

FILE* fin, * fout1/*fout2,*fout3,*fout4,*fout5,*fout6,*fout7  ע�������ļ�ָ��*/;

int coun;

std::random_device rd;     //���������ȡ�����������
std::mt19937_64 eng(rd()); //ʹ��64λ�����������
						   //ȡ���޷������������
std::uniform_int_distribution<unsigned long long> distr(1, 600);//ȡ��1~600���������

struct stu {
	int bh;	//ѧ����ţ�����ûʲô��
	char name[7];	//ѧ������
	int fl;	//flag��������¼�Ƿ�ʹ�ã��ں���������������
}stud[54];	//ѧ��������

struct stab {
	char stname[7];
}table[9][8];//��λ��

//ifstream ou1;
//ou1.open("sss.txt",ios_base::in);
//inf.open("d://�����ļ�.TXT");
//���õĲ����ļ�������

inline int ran() {
	int n = distr(eng);

	//	for(int i=1;i<=n;++i)
	//	{
	//		int mp=distr(eng);
	//	}
	//	n=distr(eng);
	//	return abs(distr(eng)%53);
	//����ʹ�ù�����������ɴ���

	srand(time(0));	//��ü����ʱ���������
	int rans = rand() + distr(eng);	//���������
	//	rans*=19260817;
	rans = abs(rans / n);	//ȡ������
	//	cout<<n<<' ';
	return rans % 53 + 1;	//������1�����������
}//���������

inline int topic() {
	char pd;
	cout << "          ��ӭʹ��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);//�����ı���ɫ
	cout << "��λ�������������Դ��V1.7.1" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << "����Ϊע�����" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "1.�˳���Ŀǰֻ�����ڹ㻪��ѧ������2���ࣨ53�ˣ���λ�����ɣ����๦�ܵȴ��������¡�" << endl;
	cout << "2.��ȷ���ڴ����г���.exe��ͬһĿ¼�����ļ��������ļ�.TXT���������ѽ�ѧ�����������д����ı��ĵ���" << endl;
	cout << "3.���������ϻ���ͬһĿ¼������7������λ��i.txt�����ļ�����������֧�֣���ѡȡ���ʺ���ճ����Excel��WPS��񼴿ɡ���������  һ������һ�������Խ��бȽϡ�" << endl;
	cout << "4.�������������һ����λ���ʱ��ԼΪ5ms(��ʹ�ó�������ʱ����һ����ϵ�����ܻ���ֳ���10������)��ռ�ü�����ڴ�1004KB��" << endl << "  ����ƽ̨��Intel(R) Core(TM) i7-8565U CPU @ 1.80GHz 1.99GHz ��̬����Ƶ�ʣ�4.6GHz" << endl << "  ��װ�����ڴ棺8GB " << endl << "  Windows�汾��Windows 10 ��ͥ���İ� 2004 19041.329" << endl;
	cout << "5.����bug���뼰ʱ��ϵ������Ա��" << endl;
	cout << "=====================================================";
	cout << "\nv1.7.1�������ݣ�\n(1)�Ż������λ������������ٶ�\n(2)����ȫ�¿�������뷽ʽ���ڴ�ռ�ü�С\n(3)���v1.7.0�ϸ߸��ʳ�ʱ�����" << endl;
	cout << "-----------------------------------------------------";
	cout << "\nv2.0�汾Ԥ�棺\n(1)�����ײ���룬ʹ���и��Ӹ�Ч\n(2)����Java��Python���ֱ�дģʽ���ṩ����Ŀ�ƽ̨����\n(3)���ѿ���̨��������ӵ�и����Ի����û���������" << endl;
	cout << "=====================================================";
	cout << "\n����Ѿ�ȷ�����������롰y/Y�������¡�Enter����ʼ���������������ַ������¡�Enter���˳���" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	pd = getchar();
	if (pd == 'y' || pd == 'Y') return 1;
	else	return 0;
}//ע������

inline void init() {
	for (int i = 1; i <= 53; ++i)
	{
		fscanf(fin, "%d %s", &stud[i].bh, &stud[i].name, 10);	//������C++17��׼���ļ������ʽ
		stud[i].fl = 0;
	}
	//	table[8][5].stname=table[8][6].stname=table[8][7].stname;
}//��ʼ�������

inline void tablec() {
	int count = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "�� ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "�� ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << "�� ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "......" << endl;
	for (int i = 1; i <= 8; ++i)
	{
		for (int j = 1; j <= 7; ++j)
		{
			//			unsigned int ee;���ñ���������ע��
			int ranst = ran();
			while (stud[ranst].fl == 1/*��ȡ�����Ѿ�����ǰʹ�ù�*/) {
				//				unsigned int seed;���ñ���������ע��
				ranst = ran();//��ȡһ�����ֵ
				//				printf("%d ",ranst);���ñ���������ע��
			}//ֱ��δʹ�ã�����while���
			strncpy_s(table[i][j].stname, stud[ranst].name, 6);	//����ѧ����������λ��(strncpy_sΪC++17��׼�涨)
			stud[ranst].fl = 1;	//��ʹ�ã���flag����f1Ϊ1
			count++;	//����

			if (count == 53) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				printf("������ɣ���\n");
				return;
			}	//��������ɺ������������ɣ�������֮���˳�tablec()����
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		printf("����ɣ�%d/8 ", i);	//��������������ȣ������ڰ汾���º��ٶ�̫�죬û��ʲô�о�
	}

}//������λ��

void print() {	//�ڿ���̨��ӡ��λ��
	printf("\t\t\t\t��  ̨\n");
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

void fprint() {		//���ļ����ӡ��λ��
	fprintf(fout1, "\t\t\t\t��  ̨\n");
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
	cout << "�Ƿ����⣿�����롰y���������⡱����n����ʾ�����⣬������Enter��" << endl;
	char as = getchar();
	if (as == 'y') return 1;
	else return 0;
}	//δʹ�ú���

int demain() {
	fin = fopen("�����ļ�.TXT", "r");
	fout1 = fopen("��λ��1.txt", "w");
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
}	//δʹ�ú���

int main()	//������/������
{
	fin = fopen("�����ļ�.TXT", "r");
	fout1 = fopen("��λ��1.txt", "w");

	if (topic() == 0) return 0;
	init();

	int fd;	//δʹ�ñ����������ڼ�¼ask()��������ֵ����Ϊask()δʹ�ã��˱���Ҳδʹ�ã�����ʱ���ܻᾯ�棬�����ᱨ��

	clock_t start, end;	//����ʱ�����
	start = clock();	//��¼��ʼ����ʱ��

	tablec();	//��Ҫ���в���
	print();
	fprint();

	end = clock();	//��¼��ֹ����ʱ��
	double runtime = (double)((double)end - (double)start) / CLOCKS_PER_SEC;	//������ʱ
	cout << "\n����ʱ��Ϊ��" << runtime << "s" << endl;	//�����ʱ

	system("pause");	//ϵͳ��ͣ������鿴

	return 0;

}
