#include "testbed_dimensions.h"

int main() {
  std::cout << "\nFlat Object Location 1 Dimensions\n";
  const int object1_width = 228;
  const int object1_length = 423;
  Position object1_origin = Position(865,758,0);
  Object o1(object1_origin, object1_width, object1_length);
  o1.print();

  std::cout << "3D Object Location 1 Dimensions\n";
  const int object_width = 228;
  const int object_length = 423;
  const int object_height = 109;
  Position object_origin = Position(865,758,object_height);
  Object o(object_origin, object_width, object_length);
  o.print();

  std::cout << "\nFlat Object Location 2 Dimensions\n";
  const int object2_width = 228;
  const int object2_length = 423;
  Position object2_origin = Position(454,635,0);
  Object o2(object2_origin, object2_width, object2_length);
  o2.print();

  std::cout << "3D Object Location 2 Dimensions\n";
  const int object3_width = 228;
  const int object3_length = 423;
  const int object3_height = 109;
  Position object3_origin = Position(454,635,object3_height);
  Object o3(object3_origin, object3_width, object3_length);
  o3.print();

  std::cout << "\nFlat Object Location 3 Dimensions\n";
  const int object4_width = 228;
  const int object4_length = 423;
  Position object4_origin = Position(265,47,0);
  Object o4(object4_origin, object4_width, object4_length);
  o4.print();

  std::cout << "3D Object Location 3 Dimensions\n";
  const int object5_width = 228;
  const int object5_length = 423;
  const int object5_height = 109;
  Position object5_origin = Position(265,47,object5_height);
  Object o5(object5_origin, object5_width, object5_length);
  o5.print();

}
