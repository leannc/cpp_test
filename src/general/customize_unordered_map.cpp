#include "UseCase.h"
#include <unordered_map>

/**
 * 要实现自定义的unordered_map，需要实现hash和==操作符，这样才能保证key的唯一性
 * 1.==操作符一般是在自定义结构的内部实现的
 * 2.hash函数的特化，一般是在std命名空间下实现的
 */

struct CityRecord {
  std::string city;
  std::string country;
  int population;
  double Latitude;
  double Longitude;

  bool operator==(const CityRecord &rhs) const {
    return rhs.city == city && rhs.country == country;
  }
};

namespace std {

template <> struct hash<CityRecord> {
  std::size_t operator()(const CityRecord &cr) const noexcept {
    return std::hash<std::string>()(cr.city) ^
           std::hash<std::string>()(cr.country);
  }
};
}  // namespace std

void customize_unordered_map() {
  std::unordered_map<CityRecord, int> custom_map;

  CityRecord cr1{"Beijing", "China", 10000000, 39.9, 116.3};
  const CityRecord cr2{"Shanghai", "China", 20000000, 31.2, 121.5};
  CityRecord cr3{"New York", "USA", 8000000, 40.7, 74.0};

  custom_map.insert(std::pair<CityRecord, int>{cr1, 10});
  std::cout << custom_map[cr1] << std::endl;  // 10
  custom_map[CityRecord("Beijing", "China", 10000000, 39.9, 116.3)] =
      1;  // NOTE:这里把key覆盖了，因为里面的参数与cr1是一样的
  custom_map[cr2] = 2;
  custom_map[cr3] = 3;
  std::cout << custom_map[cr1] << std::endl;  // 1
  std::cout << custom_map[cr2] << std::endl;  // 2
  std::cout << custom_map[cr3] << std::endl;  // 3
  std::cout << custom_map[CityRecord{"Tokyo", "Japan", 37000000, 35.7, 139.6}]
            << std::endl;  // 0
}
