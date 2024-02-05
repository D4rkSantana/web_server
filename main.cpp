#include "library/include/library.hpp"

int main(void)
{
    Config teste1;
    Config teste2("config.txt");

    std::cout << "= teste1: " << teste1.getNameFile() << std::endl;
    std::cout << "= teste2: " << teste2.getNameFile() << std::endl;

    if (teste1.readConfig())
    {
        std::cout << "* default config read is failed *" << std::endl;
    }
    if (teste2.readConfig())
    {
        std::cout << "* " << teste2.getNameFile() << " read is failed *" << std::endl;
    }
    std::cout << "= teste1 open: " << teste1.getRawConfigOpen() << std::endl;
    std::cout << "= teste2 open: " << teste2.getRawConfigOpen() << std::endl;
    std::cout << "= teste1 cont: " << std::endl << teste1.getRawConfig() << std::endl;
    std::cout << "= teste2 cont: " << std::endl << teste2.getRawConfig() << std::endl;
    return (0);
}