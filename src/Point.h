#ifndef GRIDS_POINT_H
#define GRIDS_POINT_H

#include <string>

/**
 * Class that represents a point on a Cartesian Plane.
 */
class Point {
private:
    double x_;
    double y_;
public:
    // Constructor
    Point(double x, double y);

    // Immutable accessor.
    double getX() const;

    // Immutable accessor.
    double getY() const;

    // toString.
    std::string toString() const;
};

#endif //GRIDS_POINT_H
