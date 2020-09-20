#include "Bitset.h"
#include <sstream>

using namespace std;

/**
 * Default constructor for this class.
 *
 * This just calls the constructor from the vector class.
 */
Bitset::Bitset() : std::vector<bool>() {}

/**
 * Two  argument constructor for the Bitset class.
 *
 * This just uses the constructor from the vector class.
 *
 * @param size initial size of the vector.
 * @param val default value of each element in the vector.
 */
Bitset::Bitset(unsigned long size, bool val) : std::vector<bool>(size, val) {}

/**
 * & operator overload for the Bitset class.
 *
 * This was implemented with the following properties of binary operations AND:
 * - Binary number starts from right to left.
 * - Shorter binary gets padded to have the same size as the bigger binary number.
 *
 * i.e:  1001 0011 & 1010 -> 1001 0011 & 0000 0010
 *
 * Since this is an AND operator, we can just ignore the extra bits that's being
 * operated with the padding.
 *
 * i.e: 1001 0011 & 1010 -> 1001 0011 & 0000 0010 = 0000 0010
 *
 * @param bs2 the other Bitset that this functions is going to do the operation with.
 * @return result of the AND operator between two Bitset.
 */
Bitset Bitset::operator&(const Bitset &bs2) {
    Bitset b2_local = bs2;

    Bitset *longer = size() > bs2.size() ? this : &b2_local;
    Bitset *shorter = longer == this ? &b2_local : this;

    auto longer_size = longer->size() - 1;
    auto shorter_size = shorter->size() - 1;

    // Make an empty Bitset with the size of the bigger Bitset
    Bitset out(longer->size(), false);
    // Then set elements to the result of the & operator between two bits
    for (int i = 0; i < shorter->size(); i++)
        out[(out.size() - 1 ) - i] = longer->at(longer_size - i) && shorter->at(shorter_size - i);

    return out;
}

/**
 * Adapted string representation of this class.
 *
 * This class takes another param called print_size so it can be printed with a specific bit size.
 * It just pads zeros in-front of the bitset.
 *
 * i.e: 0010 -> toString(8) -> 0000 0010.
 *
 * @param print_size the print size of this bitset.
 * @param delimiter a separator between each bits.
 * @return Adapted representation of this BitGrid.
 */
string Bitset::toString(int print_size, const char *delimiter = "") const {
    stringstream ss;
    int start = ((int) size()) - print_size;
    for (int i = start; i < (int) size(); i++)
        ss << (i >= 0 && at(i)) << (i == size() - 1 ? "" : delimiter);
    return ss.str();
}

/**
 * String representation of this bitset with size retention.
 *
 * This takes in a delimiter param just so that I can print each bitset clearly with a space ( for
 * better printing when it comes to grids.)
 *
 * i.e: 0001 -> toString(" ") -> 0 0 0 1.
 *
 * @param delimiter
 * @return string representation of this BitGrid.
 */
string Bitset::toString(const char *delimiter = "") const {
    return toString(size(), delimiter);
}



