#include "testbed_dimensions.h"

int main() {
  std::cout << "Static Black Object Dimensions\n";
  const int object_width = 258;
  const int object_length = 511;
  Position object_origin = Position(66,840,0);
  Object o(object_origin, object_width, object_length);
  o.print();
  
  std::cout << "\nOrange Object Location 1 Dimensions\n";
  const int object1_width = 258;
  const int object1_length = 511;
  Position object1_origin = Position(901,840,0);
  Object o1(object1_origin, object1_width, object1_length);
  o1.print();
  
  std::cout << "\nOrange Object Location 2 Dimensions\n";
  const int object2_width = 258;
  const int object2_length = 511;
  Position object2_origin = Position(614,840,0);
  Object o2(object2_origin, object2_width, object2_length);
  o2.print();

  std::cout << "\nBlack Object Location 3 Dimensions\n";
  const int object3_width = 258;
  const int object3_length = 511;
  Position object3_origin = Position(509,840,0);
  Object o3(object3_origin, object3_width, object3_length);
  o3.print();

  std::cout << "\nBlack Object Location 4 Dimensions\n";
  const int object4_width = 258;
  const int object4_length = 511;
  Position object4_origin = Position(462,840,0);
  Object o4(object4_origin, object4_width, object4_length);
  o4.print();

  std::cout << "\nBlack Object Location 5 Dimensions\n";
  const int object5_width = 258;
  const int object5_length = 511;
  Position object5_origin = Position(396,840,0);
  Object o5(object5_origin, object5_width, object5_length);
  o5.print();

  std::cout << "\nBlack Object Location 6 Dimensions\n";
  const int object6_width = 258;
  const int object6_length = 511;
  Position object6_origin = Position(324,840,0);
  Object o6(object6_origin, object6_width, object6_length);
  o6.print();

  std::cout << "\nBlack Object Location 7 Dimensions\n";
  const int object7_width = 258;
  const int object7_length = 511;
  Position object7_origin = Position(194,840,0);
  Object o7(object7_origin, object7_width, object7_length);
  o7.print();

}
