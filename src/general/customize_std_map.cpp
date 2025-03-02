#include "UseCase.h"
#include <map>
#include <regex>

/**
 * 要实现自定义的map，需要实现<操作符，以便map可以比较key的大小
 */

struct CityRecord {
  std::string city;
  std::string country;
  int population;
  double Latitude;
  double Longitude;

  bool operator<(const CityRecord &rhs) const {
    if (country == rhs.country) {
      return rhs.city < city;
    }
    return rhs.country < country;
  }
};

void customize_std_map() {
  std::map<CityRecord, int> custom_map;

  CityRecord cr1{"Beijing", "China", 10000000, 39.9, 116.3};
  const CityRecord cr2{"Shanghai", "China", 20000000, 31.2, 121.5};
  CityRecord cr3{"New York", "USA", 8000000, 40.7, 74.0};

  custom_map.insert(std::pair<CityRecord, int>{cr1, 9});
  std::cout << custom_map[cr1] << std::endl;  // 9
  custom_map[CityRecord("Beijing", "China", 10000000, 39.9, 116.3)] =
      1;  // NOTE:这里把key覆盖了，因为里面的参数与cr1是一样的
  custom_map[cr2] = 2;
  custom_map[cr3] = 3;
  std::cout << custom_map[cr1] << std::endl;                                                  // 1
  std::cout << custom_map[cr2] << std::endl;                                                  // 2
  std::cout << custom_map[cr3] << std::endl;                                                  // 3
  std::cout << custom_map[CityRecord{"Tokyo", "Japan", 37000000, 35.7, 139.6}] << std::endl;  // 0
}
