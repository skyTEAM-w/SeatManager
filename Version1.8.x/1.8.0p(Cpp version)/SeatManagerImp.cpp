//
// Created by HW on 2022/2/15.
//

#include <chrono>
#include "SeatManagerImp.h"
#include "Student.h"
#include "iostream"
#include "map"
#include "vector"
#include "algorithm"
#include "random"
#include "array"

using namespace std;

SeatManagerImp::SeatManagerImp() {
    File_Path = ".\\";
}

SeatManagerImp::~SeatManagerImp() = default;

void SeatManagerImp::showUI() {
    cout << "��λ���������ϵͳV1.8.0p(Cpp version)" << endl;
    cout << "-----------------------------------" << endl;
    cout << "�˰汾ΪJava���C++��ʵ�ְ档" << endl;
    cout << "1.��ʼ������λ��\n2.�鿴�Ѿ����ɵ���λ��\n3.������е���λ��\n0.�˳�ϵͳ" << endl;
}

void SeatManagerImp::makeTable() {
    ifstream ifs;
    ifs.open(File_Path + "�����ļ�.txt", ios::in);

    if (ifs.eof()) {
        cout << "�ļ������ڣ�" << endl;
        return;
    } else {
        int inNum = 0, index = 0, rowNumber, makeNumber;
        string inName;
        map<int, Student> studentMap;
        vector<int> studentKeys;

        while (ifs >> inName) {
            auto * tempStudent = new Student(inName, index + 1);
            studentMap[index] = *tempStudent;
            studentKeys.push_back(index);
            index++;
            free(tempStudent);
        }
        cout << "������ɣ���" << index + 1 << "��" << endl;

        cout << "��ѡ����Ҫ������λ���������\n";
        cin >> rowNumber;
        cout << "��������Ҫ���ɵ���λ�������\n";
        cin >> makeNumber;

        for (int i = 0; i < makeNumber; ++i) {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            shuffle(studentKeys.begin(), studentKeys.end(), std::default_random_engine(seed));
            string tempTable;
            for (int j = 0; j < index; ++j) {
                tempTable += studentMap[studentKeys[j]].getMName();
                if (j % rowNumber == 0 && j != 0) {
                    tempTable += "\n";
                } else {
                    tempTable += "\t";
                }
            }

        }
    }

}