#include <cstdlib>
#include <ctime>
#include <iostream>

#include "SpaceDefenders.hpp"

int main()
{
    std::srand(unsigned(std::time(nullptr)));

    try
    {
        SpaceDefenders game;
        game.run();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << "\n";
    }
}
