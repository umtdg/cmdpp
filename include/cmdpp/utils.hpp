#ifndef CMDPP_UTILS_HPP
#define CMDPP_UTILS_HPP

#include <string>
#include <vector>

namespace cmdpp {

    // Split string with given delimiter into vector.
    std::vector<std::string> Split(const std::string &s, char delim = ' ');

    std::string Join(const std::vector<std::string> &strings, char delim = ' ');

    bool IsEmptyOrWhitespace(const std::string &s);

} //namespace cmdpp

#endif // #ifndef CMDPP_UTILS_HPP
