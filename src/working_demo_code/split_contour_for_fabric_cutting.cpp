#include "UseCase.h"

namespace {
struct Point {
  double x;
  double y;
};

struct CZRectd {
  Point min;
  Point max;

  Point getCenter() const { return Point{(min.x + max.x) / 2, (min.y + max.y) / 2}; }
};

class CGlyContour {
 public:
  CZRectd getBoundingBox() const { return CZRectd(); }
};
}  // namespace

void split_contour_for_fabric_cutting() {
  std::vector<std::shared_ptr<CGlyContour>> p_graphs;

  CZRectd p_leftRect{{0, 0}, {0, 0}};
  CZRectd p_rightRect{{1, 1}, {1, 1}};
  std::vector<std::shared_ptr<CGlyContour>> p_leftGraphs;
  std::vector<std::shared_ptr<CGlyContour>> p_rightGraphs;

  double middle = (p_rightRect.max.x + p_leftRect.min.x) / 2;

  p_graphs.erase(std::remove_if(p_graphs.begin(), p_graphs.end(),
                                [&](const std::shared_ptr<CGlyContour>& contour) {
                                  return contour->getBoundingBox().min.x < p_leftRect.min.x ||
                                         contour->getBoundingBox().max.x > p_rightRect.max.x ||
                                         contour->getBoundingBox().min.y < p_leftRect.min.y ||
                                         contour->getBoundingBox().max.y > p_rightRect.max.y;
                                }),
                 p_graphs.end());

  std::partition_copy(p_graphs.begin(), p_graphs.end(), std::back_inserter(p_leftGraphs),
                      std::back_inserter(p_rightGraphs), [middle](const std::shared_ptr<CGlyContour>& contour) {
                        return contour->getBoundingBox().getCenter().x < middle;
                      });
}
