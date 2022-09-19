#pragma once


#include "fuction.h"

struct nameCompare {                                                                 
    bool operator()(const info& a, const info& b) const { return a.fname < b.fname; }
};



// 객체를 위한 구조체를 정의해주시고, 그 안에 operator() 함수를 만들어주면 함수 객체 준비는 끝입니다.