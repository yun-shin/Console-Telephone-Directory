#pragma once

#include <vector>
#include "info.h"

class fuction {
public:
    void finput ();
    void readFile ();
    void delData ();
    void saveFile ();
    void searchData ();
    void modifyData ();
    void backUp ();

    int fileSize (string fileName);                                                                                         //������ ũ�⸦ �������ִ� �Լ�
    string insertMinus (string phoneNum);

    void printVector ();
    void printInfo (int num);

    info data;
    vector <info> dic;
    int back;
};