#include "UI.h"
#include "fuction.h"

void UI::menu () {
    cout << "�޴�" << endl;
    cout << "1. �߰�" << endl;
    cout << "2. ����" << endl;
    cout << "3. �˻�" << endl;
    cout << "4. ����" << endl;
    cout << "5. ���" << endl;
    cout << "0. ����" << endl;
    cin >> num;
    system ("cls");
}

void UI::quickMenu () {
    fuction fuc;

    cout << "0. ��������";

    if (num == 4) {
        cout << "\t 1. �Է�" << endl;

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
        cout << "\t 2. ����" << endl;

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
        cout << "\t 1. �Է� \t 2. ����" << endl;

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