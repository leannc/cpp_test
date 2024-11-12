//
// Created by kang on 2024/11/12.
//

#include "persistenceInterface.h"
#include "textfile.h"
#include "mock.h"

void singleton_with_dependency_injection()
{
    PersistenceInterface* persistence = get_persistence_interface();
    persistence->read();
    persistence->write();

    std::cout<<std::endl;

    TextFile text_file_persistence;
    set_persistence_interface(&text_file_persistence);
    persistence = get_persistence_interface();
    persistence->read();
    persistence->write();

    std::cout<<std::endl;

    Mock mock;
    set_persistence_interface(&mock);
    persistence =get_persistence_interface();
    persistence->read();
    persistence->write();
}