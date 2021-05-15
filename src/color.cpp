#include "cmdpp/color.hpp"

#include <sstream>

namespace cmdpp {
    std::string Colored::ToColored(
            const std::string &s,
            Colors color,
            Styles style
    ) {
        std::ostringstream oss;
        oss << "\033[" << style << ';' << color << 'm' << s << "\033[0m";
        return oss.str();
    }

    void Colored::PrintColored(const std::string &s, Colors color, Styles style, std::ostream &ostream) {
        ostream << ToColored(s, color, style);
    }
}
