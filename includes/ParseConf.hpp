

#ifndef ParseConf_HPP
#define ParseConf_HPP


#include "library.hpp"


std::string readFileContents(const std::string& filename);
std::string extractServerParams(const std::string& serverBlock);
std::vector<std::string> extractLocations(const std::string& serverBlock);
std::vector<std::string> separateServerBlocks(const std::string& config);
std::string getFirstWord(const std::string& text, int position);

#endif
