#ifndef GRIDS_BITSET_H
#define GRIDS_BITSET_H

#include <vector>

/**
 * Implementation of a Bitset.
 *
 * At its core, this class is basically just a binary, represented in a vector for easy processing.
 * That means, I implemented this class with the following binary properties in mind:
 * - Binary starts from right to left.
 * - You can do binary operations (although I only implemented an AND on this one).
 * - When you do an operation to different sized binary, it will pad the smaller number
 *   with zeros. i.e. (0101 0101) & (0101) -> (0101 0101) & (0000 0101)
 *
 * I tackled this problem this way to make it easier for me to compare Grids. Since this is going to
 * be the "row" for the Grid, I can just simply do an AND operand for each row and set the result of
 * the operation to be the i'th row on the output Grid.
 */
class Bitset: public std::vector<bool> {
public:
    Bitset();

    Bitset(unsigned long size, bool val);

    // Override & bitwise operator.
    Bitset operator&(const Bitset &bs2);

    // Print normally keeping normal size.
    std::string toString(const char *delimiter) const;

    // Print this bitset with a specific size.
    std::string toString(int print_size, const char *delimiter) const;
};


#endif
