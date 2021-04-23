#include <sstream>
#include <string>
#include <vector>

namespace libcmd {

    // Split string with given delimiter into 'result'.
    template<typename Out>
    void split(const std::string &s, char delim, Out result) {
        std::istringstream iss(s);
        std::string token;
        while (std::getline(iss, token, delim)) {
            *result++ = token;
        }
    }

    // Split string with given delimiter into vector.
    std::vector<std::string> split(const std::string &s, char delim);

} //namespace libcmd

