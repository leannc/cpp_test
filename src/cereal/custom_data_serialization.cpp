#include <cereal/archives/binary.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

#include "CustomData.h"

void custom_data_serialization() {
  cereal_test::Scene scene;
  cereal_test::Point p1(10, 20);
  cereal_test::Point p2(11, 21);
  cereal_test::Point p3(12, 22);
  cereal_test::Point p4(13, 23);

  cereal_test::Polygon poly1;
  cereal_test::Polygon poly2;

  poly1.points.push_back(p1);
  poly1.points.push_back(p2);

  poly2.points.push_back(p3);
  poly2.points.push_back(p4);

  scene.elements.push_back(poly1);
  scene.elements.push_back(poly2);

  scene.polygons_map["poly1"] = poly1;
  scene.polygons_map["poly2"] = poly2;

  scene.points_map["p1"] = std::make_unique<cereal_test::Point>(p1);
  scene.points_map["p2"] = std::make_unique<cereal_test::Point>(p2);
  scene.points_map["p3"] = std::make_unique<cereal_test::Point>(p3);
  scene.points_map["p4"] = std::make_unique<cereal_test::Point>(p4);

  {
    std::ofstream ofs("data.bin", std::ios::binary);
    cereal::BinaryOutputArchive oarchive(ofs);
    oarchive(scene);
  }

  cereal_test::Scene scene2;
  std::ifstream ifs("data.bin", std::ios::binary);
  cereal::BinaryInputArchive iarchive(ifs);
  iarchive(scene2);

  std::cout << "=========elements" << std::endl;
  for (const auto& element : scene2.elements) {
    for (const auto& point : element.points) {
      std::cout << point.x << " " << point.y << std::endl;
    }
  }

  std::cout << "=========polygons_map" << std::endl;
  for (const auto& polygon : scene2.polygons_map) {
    std::cout << polygon.first << std::endl;
    for (const auto& point : polygon.second.points) {
      std::cout << point.x << " " << point.y << std::endl;
    }
  }

  std::cout << "=========points_map" << std::endl;
  for (const auto& point : scene2.points_map) {
    std::cout << point.first << std::endl;
    std::cout << point.second->x << " " << point.second->y << std::endl;
  }
}
