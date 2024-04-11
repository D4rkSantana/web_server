#include "lib.hpp"

std::string openConfigFile(void)
{
    std::ifstream   file("config_model");
    std::string     line;
    std::string     result = "";

    if (!file.is_open())
    {
        std::cerr << "file error" << std::endl;
        return ("");
    }
    while (std::getline(file, line))
        result = result + line + "\n";
    file.close();
    return (result);
}