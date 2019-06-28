#include "MineSweeper.hpp"
#include <iostream>

int main()
{
    MineSweeper test(EASY);

    int y, x, z;
    while (true)
    {
        std::cout << "Move: ";
        std::cin >> y >> x >> z;
        if(y <= -1 || x <= -1) break;
        test.Move(y,x,z);
    }
}