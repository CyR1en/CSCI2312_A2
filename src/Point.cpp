#include "Point.h"
#include <sstream>
using namespace std;

/**
  * 2 param constructor for this class.
  *
  * @param x x-coordinate value for the point.
  * @param y y-coordinate value for the point.
  */
Point::Point(double x, double y) : x_(x), y_(y) {}

/**
 * Immutable accessor for the x-coordinate of the point.
 *
 * @return x-coordinate of the point.
 */
double Point::getX() const { return x_; }

/**
* Immutable accessor for the y-coordinate of the point.
*
* @return y-coordinate of the point.
*/
double Point::getY() const { return y_; }

/**
 * Immutable string representation of the point for easy printing.
 *
 * @return string representation of the point.
 */
string Point::toString() const {
    std::stringstream ss;
    ss << "(" << getX() << ", " << getY() << ")";
    return ss.str();
}