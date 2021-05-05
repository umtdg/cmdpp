#include "cmdpp/utils.hpp"

#include <iterator>
#include <algorithm>

namespace libcmd {

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> tokens;
        std::istringstream iss(s);
        std::string token;
        while (std::getline(iss, token, delim)) {
            if (token.empty()) continue;
            tokens.push_back(token);
        }
        return tokens;
    }

    bool is_empty_or_whitespace(const std::string &s) {
        return std::all_of(s.begin(), s.end(), isspace);
    }

} //namespace libcmd
