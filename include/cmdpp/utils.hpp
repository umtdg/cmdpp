#include <sstream>
#include <string>
#include <vector>

namespace libcmd {

    // Split string with given delimiter into vector.
    std::vector<std::string> split(const std::string &s, char delim);

    bool is_empty_or_whitespace(const std::string &s);

} //namespace libcmd
