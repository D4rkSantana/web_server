

#ifndef ParseConf_HPP
#define ParseConf_HPP


#include "library.hpp"


std::string readFileContents(const std::string& filename);
std::string extractServerParams(const std::string& serverBlock);


#endif
