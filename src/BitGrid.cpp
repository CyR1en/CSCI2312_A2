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
BitGrid::BitGrid(int _length, int _width) : std::deque<Bitset>(_length, Bitset(_width, false)),
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
 * Unlike the Bitset, a BitGrid doesn't behave like a binary number. So when doing an & operator between
 * two grids, the extra "row" or Bitset doesn't get compared with a padding (which will be a Bitset of
 * zeros if that's the case.) Instead, the extra "row" or Bitset will just get carried over to the new
 * BitGrid.
 *
 * i.e: | 0 1 |     | 0 1 |              | 0 1 |
 *      | 0 0 |  &  | 1 0 |      ->      | 0 0 |
 *                  | 1 1 |  carry over  | 1 1 |
 *
 * The reason why this class is an extension of a deque is because I want to pop the front of the bigger
 * grid and compare it with the corresponding index from the smaller grid. The remaining elements of the
 * bigger grid will then be inserted to the output grid as a carry over.
 *
 * @param grid2 The grid that were going to be operating with.
 * @return A BitGrid with the result of the operation.
 */
BitGrid BitGrid::operator&(const BitGrid &grid2) {
    BitGrid g2_local = grid2;

    // used pointers because "this" is a pointer and it's easier to deal with.
    BitGrid *longer = size() > grid2.size() ? this : &g2_local;
    BitGrid *shorter = longer == this ? &g2_local : this;

    BitGrid out(shorter->getLength(), shorter->getWidth());
    for (int i = 0; i < shorter->size(); i++) {
        out[i] = longer->front() & shorter->at(i);
        longer->pop_front();
    }

    if (!longer->empty())
        out.insert(out.end(), longer->begin(), longer->end());

    // Change size of bit after operation.
    out.setLength(longer->getLength());
    out.setWidth(longer->getWidth());
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
        auto end = i == length ? " |" : " |\n";
        ss << end;
    }
    return ss.str();
}




