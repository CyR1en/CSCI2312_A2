#include <iostream>
#include <random>
#include <sstream>
#include "BitGrid.h"

using namespace std;

/**
 * Generate a random number from a to b.
 *
 * This function isn't really practical in large application because it uses Mersenne Twister engine
 * which uses 5kb of memory for each creation. But even if that's the case, it's still more
 * "random" the rand(). So I figured it's good enough for this assignment.
 *
 * @param a Start range.
 * @param b End range.
 * @return Random number from a to b.
 */
int get_random(int a, int b) {
    random_device rd; // seeding object.
    mt19937 engine(rd()); // engine and seed it with rd;
    uniform_int_distribution<> rangeDist(a, b); // [a, b] range distribution
    return rangeDist(engine); // get random integer.
}

/**
 * Two argument constructor for BitGrid.
 *
 * This constructor just calls the constructor of deque and initializes the length
 * and the width of the grid with the params.
 *
 * @param _length length (or height) of the grid.
 * @param _width width of the grid.
 */
BitGrid::BitGrid(int _length, int _width) : std::vector<Bitset>(_length, Bitset(_width, false)),
                                            length(_length), width(_width) {}

/**
 * Get a random non-1 (false) location on the grid.
 *
 * This is a recursive function that uses the get_random() function to find a point on
 * the grid that's a non-1. It's a really simple recursive function with a base case that checks
 * if the point is a 1.
 *
 * @return a Point of a non-1 on the grid.
 */
Point &BitGrid::getRandNon1() {
    auto l = get_random(0, length - 1);
    auto w = get_random(0, width - 1);
    if (at(l).at(w) != 1)
        return *new Point(l, w);
    else
        return getRandNon1();
}

/**
 * Fills the third of this grid with 1's (true)
 *
 * Using integer division to calculate the third. Then I used the recursive function, getRandNon1()
 * to give me a guaranteed non-1 coordinate.
 */
void BitGrid::fillThird() {
    int third = (length * width) / 3;
    for (int i = 0; i < third; i++) {
        Point p = getRandNon1();
        at(p.getX()).at(p.getY()) = true;
    }
}

/**
 * & operator overload for BitGrid.
 *
 * To retain the definition of a binary operator, this function was implemented with its properties being
 * followed. So when doing an & operator between wo grids, the extra "row" or Bitset gets compared with
 * a padding (which will be a Bitset of zeros).
 *
 * i.e: | 0 1 |     | 0 1 |      | 0 1 |       | 0 1 |
 *      | 0 0 |  &  | 1 0 |  ->  | 0 0 |   &   | 0 0 |
 *                  | 1 1 |      | 0 0 |       | 1 1 |
 *
 * Since this is an AND operator, we can just ignore the extra "rows" or Bitsets that's being compared to
 * the padding and just leave the extra bitsets as the default value (Bitsets of zeros). However, on a
 * different operator, the padding must not be ignored.
 *
 * i.e: | 0 1 |     | 0 1 |      | 0 1 |       | 0 1 |     | 0 1 |
 *      | 0 0 |  &  | 1 0 |  ->  | 0 0 |   &   | 0 0 |  =  | 0 0 |
 *                  | 1 1 |      | 0 0 |       | 1 1 |     | 0 0 |
 *
 * The actual & operation is done among the "rows" or Bitset itself, and the result will just be inserted
 * to the corresponding index on the output BitGrid.
 *
 * Case if two grids have a diff length and width:
 * | 0 1 |     | 0 0 1 |    | 0 0 1 |   | 0 0 1 |   | 0 0 1 |
 * | 1 0 |  &  | 0 1 0 | -> | 0 1 0 | & | 0 1 0 | = | 0 1 0 |
 *             | 1 0 1 |    | 0 0 0 |   | 1 0 1 |   | 0 0 0 |
 *
 * @param grid2 The grid that were going to be operating with.
 * @return A BitGrid with the result of the operation.
 */
BitGrid BitGrid::operator&(const BitGrid &grid2) {
    BitGrid g2_local = grid2;

    // Used pointers because "this" is a pointer and it's easier to deal with.
    BitGrid *longer = size() > grid2.size() ? this : &g2_local;
    BitGrid *shorter = longer == this ? &g2_local : this;

    // Stuff to figure out what the width of the grid should be.
    auto longer_width = longer->getWidth();
    auto shorter_width = shorter->getWidth();
    auto out_width = longer_width > shorter_width ? longer_width : shorter_width;

    // Make an empty BitGrid with the size of the bigger BitGrid
    BitGrid out(longer->getLength(), out_width);
    // Then set elements to the result of the & operator between two Bitsets.
    for (int i = 0; i < shorter->size(); i++)
        out[i] = longer->at(i) & shorter->at(i);
    return out;
}

/**
 * Length mutator for the grid.
 *
 * @param _length new length of the grid.
 */
void BitGrid::setLength(int _length) {
    BitGrid::length = _length;
}

/**
 * Width mutator of the grid.
 *
 * @param _width new width of the grid.
 */
void BitGrid::setWidth(int _width) {
    BitGrid::width = _width;
}

/**
 * Accessor for the length (height) of the grid.
 *
 * @return length of this grid.
 */
int BitGrid::getLength() const {
    return length;
}

/**
 * Accessor for the width of the grid.
 *
 * @return width of this grid.
 */
int BitGrid::getWidth() const {
    return width;
}

/**
 * String representation of the grid.
 *
 * The fact that I passed the responsibility of printing the "row" or Bitset to the
 * Bitset class itself the printing of this class easier.
 *
 * @return a string representation of this Grid.
 */
string BitGrid::toString() const {
    stringstream ss;
    for (int i = 0; i < size(); i++) {
        ss << "| ";
        ss << at(i).toString(" ");
        auto end = i == getLength() ? " |" : " |\n";
        ss << end;
    }
    return ss.str();
}




