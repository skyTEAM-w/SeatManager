#include "iostream"
#include "Student.h"
#include "SeatManagerImp.h"

using namespace std;

int main() {
    bool isExit = false;
    auto *workspace = new SeatManagerImp();

    while (!isExit) {
        int select;
        SeatManagerImp::showUI();
        cout << "ÇëÊäÈëÄãµÄÑ¡Ôñ£º" << endl;
        cin >> select;
        switch (select) {
            case 1:
                workspace->makeTable();
                break;
            case 0:
                isExit = true;
                break;
            default:
                break;
        }
    }
    return 0;
}