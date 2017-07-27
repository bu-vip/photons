#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Position {
  public:
    Position() {
      x = 0;
      y = 0;
      z = 0;
    }
    Position(int x, int y, int z) {
      this->x = x;
      this->y = y;
      this->z = z;
    }
    const int getX() {return x;}
    const int getY() {return y;}
    const int getZ() {return z;}
    void setX(int x) {this->x = x;};
    void setY(int y) {this->y = y;};
    void setZ(int z) {this->z = z;};
    Position add(Position two) {
      return Position(
        x + two.getX(),
        y + two.getY(),
        z + two.getZ());
    }
    void print() {
      std::cout << "x = " << x << " y = " << y << " z = " << z << std::endl;
    }
  private:
    int x;
    int y;
    int z;
};

// ALL CONSTANTS
// all distances in mm
const int col_spacing = 610;
const int row_spacing = 504;
const int num_rows = 3;
const int num_cols = 3;
static const Position sensor_distance_from_photon_origin = Position(-10,0,0);
static const Position source_distance_from_photon_origin = Position(30,-60,0);


Position operator+(Position one, const Position two) {
  return one.add(two);
}

class Photon {
  // the x and y origin are at the velcro corner closest to the sensor
  // the z origin is the bottom face of the case
  public:
    Photon(string name, Position origin) {
      this->name = name;
      this->origin = origin;
      sensor = origin + sensor_distance_from_photon_origin;
      source = origin + source_distance_from_photon_origin;
    } 
    void print() {
      std::cout << "Name: " << name << "\n";
      //std::cout << "origin: ";
      //origin.print();
      std::cout << "sensor: ";
      sensor.print();
      std::cout << "source: ";
      source.print();
    }
  private:
    string name;
    Position origin;
    Position sensor;
    Position source;
};


class Matrix {
  //column refers to all photons on one beam (aka all A boards are one column)
  public:
    Matrix(Position matrix_location) {
      // the matrix location is the location of A1 with respect to the
      // global origin
      this->origin = matrix_location;
      string photon_name;
      Position photon_location;
      for (int i = 0; i < num_cols; i++) {
        for (int j = 0; j < num_rows; j++) { 
          photon_name = (i+65);
          photon_name += (j+49);
          photon_location = Position(j*row_spacing, i*col_spacing,0);
          photon_location = photon_location + origin;
          photons.push_back(Photon(photon_name,photon_location));
        }
      }
    }
    void print() {
      for (int i = 0; i < photons.size(); i++) {
        photons[i].print();
      }
    }
  private:
    vector<Photon> photons;
    Position origin;

};


class Floor {
  public:
    Floor(Position origin, int floor_width, int floor_length) {
      this->origin = origin;
      corner_one = Position(floor_width,0,0);
      corner_two = Position(floor_width,floor_length,0);
      corner_three = Position(0,floor_length,0);
    }
    void print() {
      std::cout << "Floor Corners\n";
      origin.print();
      corner_one.print();
      corner_two.print();
      corner_three.print();
    }
  
  private:
    // all corners labels start at the corner closest to the global origin
    // and increase in a counter-clockwise manner
    // (ex: corner two is farthest from origin)
    Position origin;
    Position corner_one;
    Position corner_two;
    Position corner_three;
};

class Object {
  public:
    Object(Position origin, int width, int length) {
      this->origin = origin;
      corner_one = Position(width, 0, 0);
      corner_one = corner_one + origin;
      corner_two = Position(width, length, 0);
      corner_two = corner_two + origin;
      corner_three = Position(0, length, 0);
      corner_three = corner_three + origin;
    }
    void print() {
      std::cout << "Object Corners\n";
      origin.print();
      corner_one.print();
      corner_two.print();
      corner_three.print();
    }
  private:
    int length;
    int width;
    // all corners labels start at the corner closest to the global origin
    // and increase in a counter-clockwise manner
    // (ex: corner two is farthest from origin)
    Position origin;
    Position corner_one;
    Position corner_two;
    Position corner_three;
};

int main() {
  const int matrix_height = 702;
  const int matrix_x_origin = 80;
  const int matrix_y_origin = 330;
  Matrix m(Position( matrix_x_origin, matrix_y_origin, matrix_height));
  m.print();


  Position global_origin = Position(0, 0, 0);
  const int floor_width = 1225;
  const int floor_length = 2238;
  Floor f(global_origin, floor_width, floor_length);
  f.print();

  Position object_position = Position(512,56,0);
  const int object_width = 258;
  const int object_height = 511;
  Object o(object_position, object_width, object_height);
  o.print();
}
