#include <iostream>
#include "BitGrid.h"
#include "Bitset.h"
using namespace std;

int main() {
    BitGrid grid = BitGrid(2, 2);
    BitGrid grid2 = BitGrid(2, 2);

    cout << "Grid1 filled 1/3rd with ones:" << endl;
    grid.fillThird();
    cout << grid.toString() << endl;

    cout << "Grid2 filled 1/3 with ones:" << endl;
    grid2.fillThird();
    cout << grid2.toString() << endl;

    cout << "Result after Grid1 and Grid2 comparison" << endl;
    cout << (grid & grid2).toString();

    return 0;
}
