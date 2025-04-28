#include <cereal/archives/binary.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

void cereal_test() {
  std::map<std::string, std::vector<int>> my_map;
  my_map.emplace("key1", std::vector<int>{1, 2, 3});
  my_map.emplace("key2", std::vector<int>{4, 5, 6});
  my_map.emplace("key3", std::vector<int>{7, 8, 9});
  std::cout << "my_map size: " << my_map.size() << std::endl;

  std::ofstream ofs("data11.bin", std::ios::binary);
  cereal::BinaryOutputArchive oarchive(ofs);
  oarchive(my_map);

  std::map<std::string, std::vector<int>> my_map2;
  std::ifstream ifs("data11.bin", std::ios::binary);
  cereal::BinaryInputArchive iarchive(ifs);
  iarchive(my_map2);

  //   std::cout << "my_map2 size: " << my_map2.size() << std::endl;
}
