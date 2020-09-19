#ifndef GRIDS_BITGRID_H
#define GRIDS_BITGRID_H

#import <deque>

#import "Point.h"
#import "Bitset.h"

// Helper method to help me get a more "random" number.
int get_random(int a, int b);

/**
 * Implementation of a BitGrid for Programming Assignment 2.
 *
 * This is an extension of a deque of a Bitset implementation that I made.
 * See documentation for Bitset to understand why I tackled the assignment this way.
 *
 * I made this class to extend a deque of Bitset because I want to inherit all of the
 * methods that are available in the class. All I needed to do was to implement the
 * required functions to complete the assignment. I also approached the comparison
 * by overriding the AND bit operator for this class (since the definition on canvas
 * seemed like it's just doing an AND operator).
 *
 * @see Bitset
 */
class BitGrid : std::vector<Bitset> {
private:
    int length;
    int width;

    // Private recursive method to get a non 1 coordinate on the Grid.
    Point &getRandNon1();

public:
    BitGrid(int _length, int _width);

    // Compare this grid with grid 2 and generate a new one that has 1
    // in every coord where this grid and grid2 have a 1s.
    BitGrid operator&(const BitGrid &grid2);

    // Fill 1/3rd of the grid with 1s.
    void fillThird();

    // length accessor.
    int getLength() const;

    // width accessor.
    int getWidth() const;

    // length mutator.
    void setLength(int length);

    // width mutator.
    void setWidth(int width);

    // toString for this class.
    std::string toString() const;
};

#endif
