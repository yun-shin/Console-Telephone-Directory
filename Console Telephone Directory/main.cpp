
#include <fstream> // 파일 입출력
#include <string>

#include <cstring> // strtok 사용
#include <stdlib.h> // system("cls");
#include <conio.h> // getch()

#include <algorithm>

#include "fuction.h"
#include "UI.h"

int main () {
    info data;
    fuction fuc;
    UI ui;
    int check;

    fuc.readFile ();        // 데이터 읽기
    fuc.backUp ();          // 혹시 모를 사태에 대비해 처음 열때마다 데이터 백업

    while (true) {

        ui.menu ();
        fuc.readFile ();        // adress도 맞춤

        switch (ui.num) {

        case 1:
            fuc.finput ();              // 추가
            cout << endl;

            ui.quickMenu ();
            break;

        case 2:
            fuc.printVector ();         // 삭제
            cout << endl;

            fuc.delData ();
            cout << endl;

            check = fuc.back;

            ui.noOverlap (check);
            break;

        case 3:
            fuc.searchData ();          // 검색
            cout << endl;

            ui.quickMenu ();
            break;

        case 4:
            fuc.printVector ();         // 수정
            cout << endl;

            fuc.modifyData ();
            cout << endl;

            check = fuc.back;

            ui.noOverlap (check);
            break;

        case 5:
            fuc.printVector ();         // 목록
            cout << endl;

            ui.quickMenu ();
            break;

        case 0:
            return 0;                   // 종료
        }
    }
}