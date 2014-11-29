#ifndef UTILITY_HPP_INCLUDED
#define UTILITY_HPP_INCLUDED

#include <sstream>
#include <string>
#include <cmath>

template <class T>
std::string toString(T val)
{
    std::stringstream ss;
    ss << val;
    return ss.str();
}

#endif //UTILITY_HPP_INCLUDED
