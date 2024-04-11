

#ifndef FT_TO_STRING_TPP
#define FT_TO_STRING_TPP


#include "./Libs.hpp"

template <typename T>

std::string to_string(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

#endif