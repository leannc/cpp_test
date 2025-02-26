#include "UseCase.h"


void data_type_overflow() {
    std::vector<double> empty_vec;

    size_t i = 1000;

    int j = 1000;

    int place = empty_vec.size()-1;
    auto place_2 = empty_vec.size()-1;

    if (i < empty_vec.size()-1) {
        std::cout << "wrong, size_t(i) should be greater than empty_vec size" << std::endl;
    }

    if (j < empty_vec.size()-1) {
        std::cout << "wrong, int(j) should be greater than empty_vec size" << std::endl;
    }
}
