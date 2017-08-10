#include "testbed_dimensions.h"

int main() {
  const int matrix_height = 705;
  const int matrix_x_origin = 80;
  const int matrix_y_origin = 330;
  Matrix m(Position( matrix_x_origin, matrix_y_origin, matrix_height));
  m.print();


  Position global_origin = Position(0, 0, 0);
  const int floor_width = 1225;
  const int floor_length = 2238;
  Floor f(global_origin, floor_width, floor_length);
  f.print();

}
