#include <iostream>
#include "BitGrid.h"

using namespace std;

int main() {
    BitGrid grid = BitGrid(16, 32);
    BitGrid grid2 = BitGrid(16, 32);

    cout << "Grid1 filled 1/3rd with ones:" << endl;
    grid.fillThird();
    cout << grid.toString() << endl;

    cout << "Grid2 filled 1/3 with ones:" << endl;
    grid2.fillThird();
    cout << grid2.toString() << endl;

    cout << "Result after Grid1 and Grid2 comparison" << endl;
    BitGrid grid3 = grid & grid2;
    cout << grid3.toString();

    return 0;
}
