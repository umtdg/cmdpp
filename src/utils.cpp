#include "cmdpp/utils.hpp"

#include <algorithm>
#include <sstream>

namespace cmdpp {

    std::vector<std::string> Split(const std::string &s, char delim) {
        std::vector<std::string> tokens;
        std::istringstream iss(s);
        std::string token;
        while (std::getline(iss, token, delim)) {
            if (token.empty()) continue;
            tokens.push_back(token);
        }
        return tokens;
    }

    std::string Join(const std::vector<std::string> &strings, char delim) {
        std::ostringstream oss;
        size_t i, len = strings.size();

        if (len == 0) return "";

        for (i = 0; i < len - 1; i++) {
            oss << strings[i] << delim;
        }
        oss << strings[i];

        return oss.str();
    }

    bool IsEmptyOrWhitespace(const std::string &s) {
        return std::all_of(s.begin(), s.end(), isspace);
    }

} //namespace cmdpp
