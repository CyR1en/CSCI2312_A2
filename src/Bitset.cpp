#include "Bitset.h"
#include <sstream>

using namespace std;

Bitset::Bitset() : std::vector<bool>() {}

Bitset::Bitset(unsigned long size, bool val) : std::vector<bool>(size, val) {}

Bitset Bitset::operator&(const Bitset &bs2) {
    unsigned long bs2_size = bs2.size();
    unsigned long this_size = size();

    Bitset out(bs2_size > this_size ? this_size : bs2_size, false);
    unsigned long out_size = out.size();

    for (int i = 0; i < out.size(); i++)
        if (at((this_size - 1) - i) && bs2.at((bs2_size - 1) - i))
            out[(out_size - 1) - i] = true;

    if (this_size != bs2_size)
        out.insert(out.begin(), bs2_size > this_size ? bs2.begin() : begin(),
                   bs2_size > this_size ? bs2.end() - out_size : end() - out_size);

    return out;
}

string Bitset::toString(int print_size, const char *delimiter = "") const {
    stringstream ss;
    int start = ((int) size()) - print_size;
    for (int i = start; i < (int) size(); i++)
        ss << (i >= 0 && at(i)) << (i == size() - 1 ? "" : delimiter);
    return ss.str();
}

string Bitset::toString(const char *delimiter = "") const {
    return toString(size(), delimiter);
}



