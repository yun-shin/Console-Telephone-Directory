#pragma once


#include "fuction.h"

struct nameCompare {                                                                 
    bool operator()(const info& a, const info& b) const { return a.fname < b.fname; }
};



// ��ü�� ���� ����ü�� �������ֽð�, �� �ȿ� operator() �Լ��� ������ָ� �Լ� ��ü �غ�� ���Դϴ�.