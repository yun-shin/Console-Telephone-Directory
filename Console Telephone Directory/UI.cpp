#include "UI.h"
#include "fuction.h"

void UI::menu () {
    cout << "메뉴" << endl;
    cout << "1. 추가" << endl;
    cout << "2. 삭제" << endl;
    cout << "3. 검색" << endl;
    cout << "4. 수정" << endl;
    cout << "5. 목록" << endl;
    cout << "0. 종료" << endl;
    cin >> num;
    system ("cls");
}

void UI::quickMenu () {
    fuction fuc;

    cout << "0. 이전으로";

    if (num == 4) {
        cout << "\t 1. 입력" << endl;

        cin >> num;

        switch (num) {
        case 0:
            system ("cls");
            break;

        case 1:
            system ("cls");
            fuc.finput ();
            break;
        }
    }
    else if (num == 1) {
        cout << "\t 2. 수정" << endl;

        cin >> num;

        switch (num) {
        case 0:
            system ("cls");
            break;

        case 2:
            system ("cls");
            fuc.modifyData ();
            break;
        }
    }
    else {
        cout << "\t 1. 입력 \t 2. 수정" << endl;

        cin >> num;

        switch (num) {
        case 0:
            system ("cls");
            break;

        case 1:
            system ("cls");
            fuc.finput ();
            break;

        case 2:
            system ("cls");
            fuc.printVector ();
            cout << endl;

            fuc.modifyData ();
            break;
        }
    }
}

void UI::noOverlap (int check) {
    if (check > 0) {
        check = 0;
        system ("cls");
        return;
    }
    else { quickMenu (); }
}