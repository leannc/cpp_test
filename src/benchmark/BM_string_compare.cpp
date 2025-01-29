#include "UseCase.h"



void BM_string_compare(benchmark::State& state)
{
      for (auto _ : state)
      {
            std::string s1 = "Hello, World!";
            std::string s2 = "Hello, World!";
      }
}