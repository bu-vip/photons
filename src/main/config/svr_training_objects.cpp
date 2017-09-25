#include "testbed_dimensions.h"

int main() {
  std::cout << " Dimensions\n";
  const int object_width = 258;
  const int object_length = 511;
  Position object_origin = Position(66,840,0);
  Object o(object_origin, object_width, object_length);
  o.print();

}
