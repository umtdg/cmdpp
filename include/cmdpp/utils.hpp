#ifndef CMDPP_UTILS_H
#define CMDPP_UTILS_H

#include <string>
#include <vector>

namespace libcmd {

    // Split string with given delimiter into vector.
    std::vector<std::string> Split(const std::string &s, char delim);

    bool IsEmptyOrWhitespace(const std::string &s);

} //namespace cmdpp

#endif // #ifndef CMDPP_UTILS_H
