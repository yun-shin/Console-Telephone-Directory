

#include <fstream> // ���� �����
#include <string>

#include <cstring> // strtok ���
#include <stdlib.h> // system("cls");

#include <algorithm>

#include "fuction.h"
#include "Compare.h"

void fuction::finput () {
    ofstream file;
    file.open ("book.bat", ios::app);

    cout << "�߰��� �׸��� �Է����ּ���. " << endl;
    cout << "�̸� \t ��ȭ��ȣ \t �Ҽ�" << endl;

    cin >> data.fname;

    cout << " ";
    cin >> data.fnum >> data.fgroup;

    data.fnum = insertMinus (data.fnum);

    if (!data.fnum.compare ("NULL")) {
        file.close ();
        return;
    }

    file << "\n";
    file.write (data.fname.c_str (), data.fname.size ());
    file << " ";
    file.write (data.fnum.c_str (), data.fnum.size ());
    file << " ";
    file.write (data.fgroup.c_str (), data.fgroup.size ());

    //str.c_str() : C++ string -> const char* ���� ��ȯ���ִ� �Լ�


    file.close ();    //�� �ݾ��ֱ�

    cout << "����Ǿ����ϴ�." << endl;
}

void fuction::delData () {
    int eraseNum;
    string name, num, group;

    cout << endl << "���ǥ�� �� ��°�� �����Ͻðڽ��ϱ�? \t \t \t \t 0.��������" << endl;

    saveFile ();                                                                                        // eraseNum�� �Է����� �ʰ� ���α׷��� �����ϸ� ������� �ѹ� �� ����

    cin >> eraseNum;

    if (eraseNum == 0) {
        back =+ 100;
        return;
    }

    ofstream file;
    file.open ("book.bat");

    if (dic.size () >= eraseNum) {
        for (int i = 0; i < dic.size (); i++) {                                                                                 // ī���͸� ���� ������ �� -> ������ ������� ��
            if (i == eraseNum - 1) continue;

            name = dic[i].fname;
            num = dic[i].fnum;
            group = dic[i].fgroup;

            file << "\n";
            file.write (name.c_str (), name.size ());
            file << " ";
            file.write (num.c_str (), num.size ());
            file << " ";
            file.write (group.c_str (), group.size ());
        }
    }
    else {
        cout << "�ٽ� �Է��� �ּ���." << endl;
        file.close ();
        return;
    }

    file.close ();    

    cout << "�����Ǿ����ϴ�." << endl;
}

void fuction::saveFile () {
    ofstream file;
    file.open ("book.bat");

    string name, num, group;

    for (int i = 0; i < dic.size (); i++) {

        name = dic[i].fname;
        num = dic[i].fnum;
        group = dic[i].fgroup;

        file << "\n";
        file.write (name.c_str (), name.size ());
        file << " ";
        file.write (num.c_str (), num.size ());
        file << " ";
        file.write (group.c_str (), group.size ());
    }

    file.close ();    
}

void fuction::readFile () {
#pragma warning(disable: 4996)                                                          // ���� ����
    ifstream file;
    dic.reserve (100);
    dic.clear ();                                                                           // ��ø���� ���ͼ� ���� �޴µ� �ʱ�ȭ ����

    file.open ("book.bat");

                                                                                                // ����
    for (int i = 0; !file.eof (); i++) {                                                // ���� �ѹ� �� ���Ƽ� ���� Ƚ�� -1 ���ָ� ���� ���� -> input �Լ� ��ħ
        string line;
        char temp[255];

        getline (file, line);                                                               // �� ���� ����
        if (line.length () > 5) {                                                        // ù��° ��ĭ ������
                                                                                // cŸ�� ���ڿ��� ��ȯ
            strcpy (temp, line.c_str ());

            char* tok = strtok (temp, " ");                                              //�����ڴ� " "�Դϴ�.

            for (int i = 1; tok != NULL; i++) {
                if (i % 3 == 0) {
                    data.fgroup = tok;
                }
                else if (i % 2 == 0) {
                    data.fnum = tok;
                }
                else {
                    data.fname = tok;
                }

                tok = strtok (NULL, " ");
            }

            data.adress = i;
            dic.push_back (data);

            //print_info ();
        }
    }
    file.close ();

    sort (dic.begin (), dic.end (), nameCompare ());
    saveFile ();
}

void fuction::searchData () {
    int count = 0;
    string searchName, similarName[10];

    cout << endl << "�˻��� �̸�" << endl;
    cin >> searchName;

    for (int i = 0; i < searchName.length () / 2; i++) {
        similarName[i] = searchName.substr (count, 2);

        count = count + 2;
    }

    count = 0;

    for (int i = 0; i < dic.size (); i++) {

        if (dic[i].fname == searchName) {
            printInfo (i);
            cout << endl;
        }
        else {
            for (int ii = 0; ii < searchName.length () / 2; ii++) {
                if (dic[i].fname.find (similarName[ii]) >= 0 && dic[i].fname.find (similarName[ii]) < 30) { count++; }
            }

            if (count > 0) {
                printInfo (i);
                count = 0;
            }
        }
    }

    cout << "�˻� �Ϸ�." << endl;
}

void fuction::modifyData () {
    int mAdress = 0;
    string mname = "NULL", mnum = "NULL", mgroup = "NULL";

    cout << "������ ���ϴ� ���й�ȣ �Է��� �ּ���. \t \t \t \t 0. ��������" << endl;
    cin >> mAdress;
    cout << endl;

    if (mAdress == 0) { return; }
    else if (!(mAdress <= dic.size ())) {
        cout << "��ȿ�� ��ȣ�� �Է����ּ���." << endl;
        return;
    }
    else {
        cout << "������ ���ϴ� �κи� �Է��� �ּ���. ������ ������ ���� ���� '0'�� �Է����ּ���." << endl;
        cout << "(ex) �Ҽ� �� ������ �� '0 0 �Ҽ�' " << endl;
        cout << "(ex2) ��ȣ�� ������ �� '0 ��ȣ 0 '" << endl;

        cin >> mname >> mnum >> mgroup;

        if (mname.compare ("0")) { dic[mAdress - 1].fname = mname; }

        if (mnum.compare ("0")) {
            mnum = insertMinus (mnum);

            if (!mnum.compare ("NULL")) { return; }

            dic[mAdress - 1].fnum = mnum;
        }

        if (mgroup.compare ("0")) { dic[mAdress - 1].fgroup = mgroup; }

        saveFile ();

        cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
    }
}

void fuction::backUp () {
    int size;
    size = fileSize ("book.bat");

    if (size > 20) {
        ofstream file;
        file.open ("backup.bat");

        string name, num, group;

        for (int i = 0; i < dic.size (); i++) {
            name = dic[i].fname;
            num = dic[i].fnum;
            group = dic[i].fgroup;

            file << "\n";
            file.write (name.c_str (), name.size ());
            file << " ";
            file.write (num.c_str (), num.size ());
            file << " ";
            file.write (group.c_str (), group.size ());
        }
    }
}

int fuction::fileSize (string fileName) {
    struct stat _stat;                                          // ����ü / ���� ����
                                                      
    int rc = stat (fileName.c_str (), &_stat);                   // ���� ���翩�� �� ���� �Ӽ��� _stat�� �־��� �����ϸ� '0' ��ȯ
    int returnValue;

    if (rc == 0) {
        returnValue = _stat.st_size;                            //������ ũ�⸦ �����ش�.
    }
    else {
        returnValue = -1;
    }

    return returnValue;
}

string fuction::insertMinus (string phoneNum) {
    string num[14], impurity;

    for (int i = 0; i < phoneNum.length (); i++) {
        num[i] = phoneNum.substr (i);

        impurity = num[i].front ();

        if (!impurity.compare ("-")) { return phoneNum; }
    }


    if (phoneNum.size () < 5) {
        cout << endl << "�߸��Է��ϼ̽��ϴ�." << endl;
        return "NULL";
    }

    else if (phoneNum.size () < 10) {                                                               // ���� ����ȭ
        phoneNum.insert (2, "-");
        phoneNum.insert (6, "-");
    }
    else if (phoneNum.size () < 11) {                                                        // ������ȣ ����ȭ
        phoneNum.insert (3, "-");
        phoneNum.insert (7, "-");
    }
    else if (phoneNum.size () < 12) {                                                                // �޴���
        phoneNum.insert (3, "-");
        phoneNum.insert (8, "-");
    }

    return phoneNum;
                                                                        // ���ڸ� �Է��ϵ� '-'�� �ֵ� ������ '-' ����
}

void fuction::printVector () {
    cout << endl << endl;
    cout << "\t \t \t ���" << endl << endl;

    cout.width (8); cout << "����";
    cout.width (12); cout << "�̸�";
    cout.width (20); cout << "��ȭ��ȣ";
    cout.width (12); cout << "�Ҽ�" << endl << endl;

    for (int i = 0; i < dic.size (); i++) {
        cout.width (8); cout << dic[i].adress;
        cout.width (12); cout << dic[i].fname;
        cout.width (20); cout << dic[i].fnum;
        cout.width (12); cout << dic[i].fgroup;
        cout << endl;
    }
}

void fuction::printInfo (int num) {
    cout.width (8);
    cout << dic[num].adress;
    cout.width (12);
    cout << dic[num].fname;
    cout.width (20);
    cout << dic[num].fnum;
    cout.width (12);
    cout << dic[num].fgroup;
    cout << endl;
}
