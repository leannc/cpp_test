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

    int neg_int = -1;
    size_t zero_size_t = 0;
    unsigned int uint_zero = 0;

    if (neg_int > zero_size_t) {
        std::cout << "wrong, the int is converted to size_t implicitly" << std::endl;
    }

    if (neg_int < (int)zero_size_t) {
        std::cout << "right, the size_t is converted to int explicitly" << std::endl;
    }

    if (neg_int > uint_zero) {
        std::cout << "wrong, the int is converted to unsigned int implicitly" << std::endl;
    }
}
