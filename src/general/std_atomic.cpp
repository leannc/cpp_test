
// Created by kang on 2025/1/24.
//
#include "UseCase.h"
#include <atomic>
#include <array>
#include <execution>
#include <assert.h>


///atomic是能够支持 ordinary_int = atomic_int++;这种赋值操作的，这种操作是线程安全的
void std_atomic() {
   std::atomic<int> atomic_i=0;
   //  int atomic_i=0;
    std::string useless = "";

    std::array<int,100000> arr{-1};

    std::for_each(std::execution::par,arr.begin(),arr.end(),[&](int& item)
    {
       item = atomic_i++;
    });

   auto last = std::unique(arr.begin(),arr.end());
   assert(last == arr.end() && "duplication exist");
   std::cout<<"the result is right"<<std::endl;

}