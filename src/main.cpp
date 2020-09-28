#include <iostream>
#include "BitGrid.h"

using namespace std;

int main() {
    BitGrid grid = BitGrid(3, 4);
    BitGrid grid2 = BitGrid(3, 4);

    cout << "Grid1 filled 1/3rd with ones:" << endl;
    grid.fillThird();
    cout << grid << endl;

    cout << "Grid2 filled 1/3 with ones:" << endl;
    grid2.fillThird();
    cout << grid2 << endl;

    cout << "Result after Grid1 and Grid2 comparison" << endl;
    cout << (grid & grid2);


    return 0;
}
