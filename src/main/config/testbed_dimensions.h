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
    Position(float x, float y, float z) {
      this->x = x;
      this->y = y;
      this->z = z;
    }
    const float getX() {return x;}
    const float getY() {return y;}
    const float getZ() {return z;}
    void setX(float x) {this->x = x;};
    void setY(float y) {this->y = y;};
    void setZ(float z) {this->z = z;};
    Position add(Position two) {
      return Position(
        x + two.getX(),
        y + two.getY(),
        z + two.getZ());
    }
    Position subtract(Position two) {
      return Position(
        x - two.getX(),
        y - two.getY(),
        z - two.getZ());
    }
    int network_length() {
      return abs(x) + abs(y) + abs(z);
    }
    void print() {
      std::cout << "x = " << x << " y = " << y << " z = " << z << std::endl;
    }
  private:
    float x;
    float y;
    float z;
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

Position operator-(Position one, const Position two) {
  return one.subtract(two);
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
    Position getOrigin() {
      return origin;
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
    vector<Position> getPhotonCoordinates() {
      vector<Position> positions;
      for (int i = 0; i<photons.size(); i++) {
        positions.push_back(photons[i].getOrigin());
      }
      return positions;
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
    Object(Position origin, float width, float length) {
      this->origin = origin;
      corner_one = Position(width, 0, 0);
      corner_one = corner_one + origin;
      corner_two = Position(width, length, 0);
      corner_two = corner_two + origin;
      corner_three = Position(0, length, 0);
      corner_three = corner_three + origin;
      center = origin +  Position(width/2,length/2,0);
    }
    void print() {
      std::cout << "Object Corners\n";
      origin.print();
      corner_one.print();
      corner_two.print();
      corner_three.print();
      std::cout << "Object Center\n";
      center.print();
    }
    Position getCenter(){ 
      return center;
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
    Position center;
};

Position compute_origin_from_center(float width, float height, Position center) {
  return center - Position(width/2, height/2, 0);
}
