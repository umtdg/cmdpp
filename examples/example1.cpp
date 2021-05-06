// Example using std::cout and std::cin as output and input streams.

#include "cmdpp/cmd.hpp"

#include <iostream>
#include <vector>

void echo(const libcmd::Cmd::ArgType &args, std::ostream &ostream) {
    size_t argc = args.size();
    for (size_t i = 0; i < argc - 1; i++) {
        ostream << args[i] << ' ';
    }
    ostream << args[argc - 1] << '\n';
}

int main() {
    libcmd::Cmd cmd("(prompt) ");
    cmd.AddCommand("echo", echo);
    cmd.CmdLoop();

    return 0;
}
