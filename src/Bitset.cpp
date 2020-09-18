#include "Bitset.h"
#include <sstream>

using namespace std;

/**
 * Default constructor for this class.
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
 * - Shorter binary gets padded to have the same size as the bigger binary number.ß
 *
 * i.e:  1001 0011 & 1010 -> 0000 0010
 *
 * @param bs2 the other Bitset that this functions is going to do the operation with.ß
 * @return result of the AND operator between two Bitset.ß
 */
Bitset Bitset::operator&(const Bitset &bs2) {
    unsigned long bs2_size = bs2.size();
    unsigned long this_size = size();

    Bitset out(bs2_size > this_size ? this_size : bs2_size, false);
    unsigned long out_size = out.size();

    for (int i = 0; i < out.size(); i++)
        //offset to start from the last.ß
        if (at((this_size - 1) - i) && bs2.at((bs2_size - 1) - i))
            out[(out_size - 1) - i] = true;

    if (this_size != bs2_size)
        out.insert(out.begin(), bs2_size > this_size ? bs2.begin() : begin(),
                   bs2_size > this_size ? bs2.end() - out_size : end() - out_size);

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
 * @return
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
 * @return
 */
string Bitset::toString(const char *delimiter = "") const {
    return toString(size(), delimiter);
}



