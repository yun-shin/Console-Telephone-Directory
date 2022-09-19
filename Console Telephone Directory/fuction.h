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

    int fileSize (string fileName);                                                                                         //파일의 크기를 리턴해주는 함수
    string insertMinus (string phoneNum);

    void printVector ();
    void printInfo (int num);

    info data;
    vector <info> dic;
    int back;
};