#include "testbed_dimensions.h"

int main() {
  std::cout << "Object Location 1 Dimensions\n";
  const int object_width = 258;
  const int object_length = 511;
  Position object_origin = Position(838,741,0);
  Object o(object_origin, object_width, object_length);
  o.print();
}
