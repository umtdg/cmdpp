// Example using std::cout and std::cin as output and input streams.

#include "cmdpp/cmd.hpp"

#include <iostream>
#include <vector>

// maybe add to cmd.hpp
#define CmdFuncDecl(name) void name(const cmdpp::Cmd::ArgType &args, std::ostream &ostream)

CmdFuncDecl(echo) {
    size_t argc = args.size();
    if (argc == 0) return;

    for (size_t i = 0; i < argc - 1; i++) {
        ostream << args[i] << ' ';
    }
    ostream << args[argc - 1] << '\n';

    ostream.flush();
}

CmdFuncDecl(foocat) {
    ostream << "foocat\n";

    ostream.flush();
}

CmdFuncDecl(catfoo) {
    ostream << "catfoo\n";

    ostream.flush();
}

CmdFuncDecl(foo) {
    ostream << "foo\n";

    ostream.flush();
}

int main() {
    cmdpp::Cmd cmd("(prompt) ");
    cmd.AddCommand("echo", echo);
    cmd.AddCommand("foocat", foocat);
    cmd.AddCommand("catfoo", catfoo);
    cmd.AddCommand("foo", foo);
    cmd.CmdLoop();

    return 0;
}
