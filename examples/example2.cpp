// Example using a file for input and another file for output.

#include "cmdpp/cmd.hpp"
#include "cmdpp/readline.hpp"

#include <vector>
#include <string>
#include <fstream>

class example : public cmdpp::Cmd {
public:
    explicit example(std::string _prompt) :
            cmdpp::Cmd(std::move(_prompt), "bye") {}

protected:
    void PostCmd() override {
        ostream.flush();
    }

    void PreExit() override {
        ostream << "Goodbye\n";
    }
};

void echo(const cmdpp::Cmd::ArgType &args, std::ostream &ostream) {
    size_t argc = args.size();
    for (size_t i = 0; i < argc - 1; i++) {
        ostream << args[i] << ' ';
    }
    ostream << args[argc - 1] << '\n';
}

int main() {
    example cmd{"(prompt) "};
    cmd.AddCommand("echo", echo);
    cmd.CmdLoop();

    return 0;
}
