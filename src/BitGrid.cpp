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

BitGrid::BitGrid(int _length, int _width) : std::deque<Bitset>(_length, Bitset(_width, false)),
                                            length(_length), width(_width) {}

Point &BitGrid::getRandNon1() {
    auto l = get_random(0, length - 1);
    auto w = get_random(0, width - 1);
    if (at(l).at(w) != 1)
        return *new Point(l, w);
    else
        return getRandNon1();
}

void BitGrid::fillThird() {
    int third = (length * width) / 3;
    for (int i = 0; i < third; i++) {
        Point p = getRandNon1();
        at(p.getX()).at(p.getY()) = true;
    }
}

int BitGrid::getLength() const {
    return length;
}

int BitGrid::getWidth() const {
    return width;
}

BitGrid BitGrid::operator&(const BitGrid &grid2) {
    BitGrid g2_local = grid2;

    BitGrid *longer = size() > grid2.size() ? this : &g2_local;
    BitGrid *shorter = longer == this ? &g2_local : this;

    BitGrid out(shorter->getLength(), shorter->getWidth());
    for (int i = 0; i < shorter->size(); i++) {
        out[i] = longer->front() & shorter->at(i);
        longer->pop_front();
    }

    if (!longer->empty())
        out.insert(out.end(), longer->begin(), longer->end());
    return out;
}

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




