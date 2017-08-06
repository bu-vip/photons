#include "testbed_dimensions.h"

int main() {
  const int matrix_height = 0;
  const int matrix_x_origin = 0;
  const int matrix_y_origin = 0;
  const double conversion = 0.0393701;
  Matrix m(Position( matrix_x_origin, matrix_y_origin, matrix_height));
  vector<Position> photon_coordinates = m.getPhotonCoordinates();
  const Position hub_position = Position(760,610,0);
  vector<Position> cables;
  vector<int> cable_lengths;
  for (int i = 0; i < photon_coordinates.size(); i++) {
     cables.push_back(hub_position - photon_coordinates[i]);
     cables[i].print();
     cable_lengths.push_back(cables[i].network_length());
  }
  std::cout << "\n\n" << "total: " << cable_lengths.size() << "\n";
  for (int i = 0; i < cable_lengths.size(); i++) {
     std::cout << conversion*cable_lengths[i] << "\t" << cable_lengths[i];
     std::cout << "\n";
  }
}
