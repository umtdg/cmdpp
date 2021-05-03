#include "cmdpp/utils.hpp"

#include <iterator>

namespace libcmd {

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> tokens;
        std::istringstream iss(s);
        std::string token;
        while (std::getline(iss, token, delim)) {
            tokens.push_back(token);
        }
        return tokens;
    }

} //namespace libcmd
