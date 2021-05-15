#include <string>
#include <ostream>
#include <iostream>

#ifndef CMDPP_COLOR_HPP
#define CMDPP_COLOR_HPP

namespace cmdpp {
    enum Colors {
        COLOR_BLACK = 30,
        COLOR_RED = 31,
        COLOR_GREEN = 32,
        COLOR_YELLOW = 33,
        COLOR_BLUE = 34,
        COLOR_PURPLE = 35,
        COLOR_CYAN = 36,
        COLOR_WHITE = 37,
        COLOR_DEFAULT = 39,
        COLOR_BRIGHT_BLACK = 90,
        COLOR_BRIGHT_RED = 91,
        COLOR_BRIGHT_GREEN = 92,
        COLOR_BRIGHT_YELLOW = 93,
        COLOR_BRIGHT_BLUE = 94,
        COLOR_BRIGHT_PURPLE = 95,
        COLOR_BRIGHT_CYAN = 96,
        COLOR_BRIGHT_WHITE = 97
    };

    enum Styles {
        STYLE_DEFAULT = 0,
        STYLE_BOLD = 1,
        STYLE_UNDERLINE = 4
    };

    class Colored {
    public:
        static std::string ToColored(
                const std::string &s,
                Colors color = COLOR_DEFAULT,
                Styles style = STYLE_DEFAULT);

        static void PrintColored(
                const std::string &s,
                Colors color = COLOR_DEFAULT,
                Styles style = STYLE_DEFAULT,
                std::ostream &ostream = std::cout);
    };
}

#endif //CMDPP_COLOR_HPP
