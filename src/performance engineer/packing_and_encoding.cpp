//
// Created by kang on 2025/1/14.
//


#include "UseCase.h"

struct Date_1 {
    unsigned int year;
    unsigned int month;
    unsigned int day;
};

struct Date_2 {
    unsigned int year : 13;
    unsigned int month: 4;
    unsigned int day: 5;
};

void packing_and_encoding()
{
    std::cout<<"the size of Date_1 is "<<sizeof(Date_1)<<std::endl; ///用了3个int，所以需要12个byte
    std::cout<<"the size of Date_2 is "<<sizeof(Date_2)<<std::endl; ///做了位数的限制，一共只有22位，就只占了4个byte

    Date_1 date1;
    Date_2 date2;

    date1.month = 1024;
    std::cout<<"the month of date1 is "<<date1.month<<std::endl; ///正常

    date2.month = 1024;
    std::cout<<"the month of date2 is "<<date2.month<<std::endl; ///溢出了，只看低4位，就是0
}