#include "testbed_dimensions.h"

int main() {
  Position center = Position(971,786.5,0);

  std::cout << "64X Object Dimensions\n";
  const int object1_width = 258;
  const int object1_height = 511;
  Position object1_origin = compute_origin_from_center(object1_width, object1_height, center); 
  Object o(object1_origin, object1_width, object1_height);
  o.print();

  std::cout << "\n\n4X Object Dimensions\n";
  const int object5_width = 64;
  const int object5_height = 129;
  Position object5_origin = compute_origin_from_center(object5_width, object5_height, center); 
  Object o5(object5_origin, object5_width, object5_height);
  o5.print();

  std::cout << "\n\n1X Object Dimensions\n";
  const int object6_width = 32;
  const int object6_height = 64;
  Position object6_origin = compute_origin_from_center(object6_width, object6_height, center); 
  Object o6(object6_origin, object6_width, object6_height);
  o6.print();
}
