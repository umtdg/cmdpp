// Example using std::cout and std::cin as output and input streams.

#include "cmdpp/Cmd.hpp"

#include <iostream>
#include <vector>

class example : public libcmd::Cmd {
public:
    explicit example(std::string _prompt) :
            libcmd::Cmd(std::move(_prompt)) {}

    void HandleCommands(const std::string &command, std::vector<std::string> &args) override {
        if (command == "exit") {
            running = false;
        } else if (command == "echo") {
            for (const std::string &arg : args) {
                ostream << arg << '\n';
            }
        } else {
            ostream << "Command '" << command << "' not found\n";
        }

        ostream.flush();
    }
};

int main() {
    example cmd("(prompt)");
    cmd.CmdLoop();

    return 0;
}

