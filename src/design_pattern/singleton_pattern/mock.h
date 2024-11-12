//
// Created by kang on 2024/11/12.
//

#ifndef CPP_TEST_MOCK_H
#define CPP_TEST_MOCK_H

#include "persistenceInterface.h"
#include "../UseCase.h"

class Mock : public PersistenceInterface {
public:
    virtual ~Mock() = default;
    bool read () const
    {
        //do something
        do_read();
        return true;
    }

    bool write() {
        //do something
        do_write();
        return true;
    }

private:
    bool do_read() const override { std::cout<<"Mock::do_read()"<<std::endl; ;return true;};
    bool do_write() override {std::cout<<"Mock::do_write()"<<std::endl; return true;};

};

#endif //CPP_TEST_MOCK_H
