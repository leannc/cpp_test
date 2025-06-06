#include "UseCase.h"

struct path {
  int mesh_id;
  int part_id;
  int strip_id;
};

void multy_level_sort() {
  std::vector<path> paths;
  for (int i = 0; i < 100; i++) {
    int random_mesh_id =
        rand() % 10;  // Generate a random mesh_id between 0 and 99
    int random_part_id =
        rand() % 5;  // Generate a random part_id between 0 and 9
    int random_strip_id =
        rand() % 20;  // Generate a random strip_id between 0 and 9
    paths.push_back({random_mesh_id, random_part_id, random_strip_id});
  }

  std::sort(paths.begin(), paths.end(), [](const path &a, const path &b) {
    if (a.mesh_id != b.mesh_id) {
      return a.mesh_id < b.mesh_id;
    } else if (a.part_id != b.part_id) {
      return a.part_id < b.part_id;
    } else {
      return a.strip_id < b.strip_id;
    }
  });

  for (const auto &p : paths) {
    std::cout << "mesh_id: " << p.mesh_id << ", part_id: " << p.part_id
              << ", strip_id: " << p.strip_id << std::endl;
  }
}
