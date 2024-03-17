#include "lib.hpp"

int main()
{
    std::string file;

    file = openConfigFile();
    if (file != "")
        std::cout << file << std::endl;
    return (0);
}