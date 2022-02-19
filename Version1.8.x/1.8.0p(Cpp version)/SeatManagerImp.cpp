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
    cout << "座位表随机生成系统V1.8.0p(Cpp version)" << endl;
    cout << "-----------------------------------" << endl;
    cout << "此版本为Java版的C++重实现版。" << endl;
    cout << "1.开始生成座位表\n2.查看已经生成的座位表\n3.清空所有的座位表\n0.退出系统" << endl;
}

void SeatManagerImp::makeTable() {
    ifstream ifs;
    ifs.open(File_Path + "读入文件.txt", ios::in);

    if (ifs.eof()) {
        cout << "文件不存在！" << endl;
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
        cout << "读入完成，共" << index + 1 << "人" << endl;

        cout << "请选择需要生成座位表的行数：\n";
        cin >> rowNumber;
        cout << "请输入需要生成的座位表个数：\n";
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