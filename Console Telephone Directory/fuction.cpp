

#include <fstream> // 파일 입출력
#include <string>

#include <cstring> // strtok 사용
#include <stdlib.h> // system("cls");

#include <algorithm>

#include "fuction.h"
#include "Compare.h"

void fuction::finput () {
    ofstream file;
    file.open ("book.bat", ios::app);

    cout << "추가할 항목을 입력해주세요. " << endl;
    cout << "이름 \t 전화번호 \t 소속" << endl;

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

    //str.c_str() : C++ string -> const char* 으로 변환해주는 함수


    file.close ();    //꼭 닫아주기

    cout << "저장되었습니다." << endl;
}

void fuction::delData () {
    int eraseNum;
    string name, num, group;

    cout << endl << "목록표의 몇 번째를 삭제하시겠습니까? \t \t \t \t 0.이전으로" << endl;

    saveFile ();                                                                                        // eraseNum을 입력하지 않고 프로그램을 종료하면 사라져서 한번 더 저장

    cin >> eraseNum;

    if (eraseNum == 0) {
        back =+ 100;
        return;
    }

    ofstream file;
    file.open ("book.bat");

    if (dic.size () >= eraseNum) {
        for (int i = 0; i < dic.size (); i++) {                                                                                 // 카운터를 파일 끝으로 함 -> 벡터의 사이즈로 함
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
        cout << "다시 입력해 주세요." << endl;
        file.close ();
        return;
    }

    file.close ();    

    cout << "삭제되었습니다." << endl;
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
#pragma warning(disable: 4996)                                                          // 오류 씹음
    ifstream file;
    dic.reserve (100);
    dic.clear ();                                                                           // 중첩으로 나와서 먼지 햇는데 초기화 안함

    file.open ("book.bat");

                                                                                                // 정렬
    for (int i = 0; !file.eof (); i++) {                                                // 지금 한번 더 돌아서 도는 횟수 -1 해주면 오류 없음 -> input 함수 고침
        string line;
        char temp[255];

        getline (file, line);                                                               // 한 줄을 받음
        if (line.length () > 5) {                                                        // 첫번째 빈칸 안읽음
                                                                                // c타입 문자열로 변환
            strcpy (temp, line.c_str ());

            char* tok = strtok (temp, " ");                                              //구분자는 " "입니다.

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

    cout << endl << "검색할 이름" << endl;
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

    cout << "검색 완료." << endl;
}

void fuction::modifyData () {
    int mAdress = 0;
    string mname = "NULL", mnum = "NULL", mgroup = "NULL";

    cout << "수정을 원하는 구분번호 입력해 주세요. \t \t \t \t 0. 이전으로" << endl;
    cin >> mAdress;
    cout << endl;

    if (mAdress == 0) { return; }
    else if (!(mAdress <= dic.size ())) {
        cout << "유효한 번호를 입력해주세요." << endl;
        return;
    }
    else {
        cout << "수정을 원하는 부분만 입력해 주세요. 수정을 원하지 않은 곳은 '0'을 입력해주세요." << endl;
        cout << "(ex) 소속 만 수정할 때 '0 0 소속' " << endl;
        cout << "(ex2) 번호만 수정할 때 '0 번호 0 '" << endl;

        cin >> mname >> mnum >> mgroup;

        if (mname.compare ("0")) { dic[mAdress - 1].fname = mname; }

        if (mnum.compare ("0")) {
            mnum = insertMinus (mnum);

            if (!mnum.compare ("NULL")) { return; }

            dic[mAdress - 1].fnum = mnum;
        }

        if (mgroup.compare ("0")) { dic[mAdress - 1].fgroup = mgroup; }

        saveFile ();

        cout << "수정이 완료되었습니다." << endl;
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
    struct stat _stat;                                          // 구조체 / 버퍼 생성
                                                      
    int rc = stat (fileName.c_str (), &_stat);                   // 파일 존재여부 및 파일 속성을 _stat에 넣어줌 존재하면 '0' 반환
    int returnValue;

    if (rc == 0) {
        returnValue = _stat.st_size;                            //파일의 크기를 구해준다.
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
        cout << endl << "잘못입력하셨습니다." << endl;
        return "NULL";
    }

    else if (phoneNum.size () < 10) {                                                               // 서울 집전화
        phoneNum.insert (2, "-");
        phoneNum.insert (6, "-");
    }
    else if (phoneNum.size () < 11) {                                                        // 지역번호 집전화
        phoneNum.insert (3, "-");
        phoneNum.insert (7, "-");
    }
    else if (phoneNum.size () < 12) {                                                                // 휴대폰
        phoneNum.insert (3, "-");
        phoneNum.insert (8, "-");
    }

    return phoneNum;
                                                                        // 숫자만 입력하든 '-'를 넣든 무조건 '-' 넣음
}

void fuction::printVector () {
    cout << endl << endl;
    cout << "\t \t \t 목록" << endl << endl;

    cout.width (8); cout << "구분";
    cout.width (12); cout << "이름";
    cout.width (20); cout << "전화번호";
    cout.width (12); cout << "소속" << endl << endl;

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
