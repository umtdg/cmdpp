// Example using std::cout and std::cin as output and input streams.

#include "cmdpp/cmd.hpp"

#include <iostream>
#include <vector>

// maybe add to cmd.hpp
#define CmdFuncDecl(name) void name(const cmdpp::Cmd::ArgType &args)

class example : public cmdpp::Cmd {
public:
    explicit example(std::string _prompt) : cmdpp::Cmd(std::move(_prompt)) {

    }
};

cmdpp::Cmd::RetCode Echo(std::ostream &ostream, const cmdpp::Cmd::ArgType &args) {
    size_t argc = args.size();
    if (argc == 0)
        return cmdpp::Cmd::RET_OK;

    for (size_t i = 0; i < argc - 1; i++) {
        ostream << args[i] << " ";
    }
    ostream << args[argc - 1] << std::endl;

    return cmdpp::Cmd::RET_OK;
}

cmdpp::Cmd::RetCode Exit(std::ostream &ostream, const cmdpp::Cmd::ArgType &args) {
    (void)args;

    ostream << "Exiting..." << std::endl;

    return cmdpp::Cmd::RET_EXIT;
}

int main() {
    example cmd("(prompt) ");
    cmd.AddCommand("echo", Echo);
    cmd.AddCommand("exit", Exit);
    cmd.CmdLoop();

    return 0;
}
