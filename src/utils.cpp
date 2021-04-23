#include "cmdpp/utils.hpp"

#include <iterator>

namespace libcmd {

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> tokens;
        split(s, delim, std::back_inserter(tokens));
        return tokens;
    }

} //namespace libcmd
