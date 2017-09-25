#include "testbed_dimensions.h"

int main() {
  std::cout << "\n\nPart 2\n\n";
  std::cout << "\nFlat Object Location 1 Dimensions\n";
  const int object1_width = 258;
  const int object1_length = 511;
  Position object1_origin = Position(850,714,0);
  Object o1(object1_origin, object1_width, object1_length);
  o1.print();

  std::cout << "\n3D Object Location 1 Dimensions\n";
  const int object_width = 258;
  const int object_length = 511;
  const int object_height = 165;
  Position object_origin = Position(850,714,object_height);
  Object o(object_origin, object_width, object_length);
  o.print();

  std::cout << "\nFlat Object Location 2 Dimensions\n";
  const int object2_width = 258;
  const int object2_length = 511;
  Position object2_origin = Position(439,591,0);
  Object o2(object2_origin, object2_width, object2_length);
  o2.print();

  std::cout << "\n3D Object Location 2 Dimensions\n";
  const int object3_width = 258;
  const int object3_length = 511;
  const int object3_height = 165;
  Position object3_origin = Position(439,591,object3_height);
  Object o3(object3_origin, object3_width, object3_length);
  o3.print();

  std::cout << "\nFlat Object Location 3 Dimensions\n";
  const int object4_width = 258;
  const int object4_length = 511;
  Position object4_origin = Position(250,3,0);
  Object o4(object4_origin, object4_width, object4_length);
  o4.print();

  std::cout << "\n3D Object Location 3 Dimensions\n";
  const int object5_width = 258;
  const int object5_length = 511;
  const int object5_height = 165;
  Position object5_origin = Position(250,3,object5_height);
  Object o5(object5_origin, object5_width, object5_length);
  o5.print();


}
