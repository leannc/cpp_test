//
// Created by kang on 2024/11/12.
//

#ifndef CPP_TEST_PERSISTENCEINTERFACE_H
#define CPP_TEST_PERSISTENCEINTERFACE_H

#include "../UseCase.h"
class PersistenceInterface {
public:
    virtual ~PersistenceInterface() = default;
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
    virtual bool do_read() const =0;
    virtual bool do_write() =0;

};

PersistenceInterface* get_persistence_interface();
void set_persistence_interface(PersistenceInterface* persistence);

extern PersistenceInterface* instance;

#endif //CPP_TEST_PERSISTENCEINTERFACE_H
