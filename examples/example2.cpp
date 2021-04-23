// Example using a file for input and another file for output.

#include "cmdpp/Cmd.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

class example : public libcmd::Cmd {
public:
    explicit example(std::string _prompt, std::ostream &_ostream, std::istream &_istream) :
            libcmd::Cmd(std::move(_prompt), _ostream, _istream) {}

protected:
    void HandleCommands(const std::string &command, std::vector<std::string> &args) override {
        ostream << command << '\n';

        if (command == "exit") {
            running = false;
        } else if (command == "echo") {
            size_t argc = args.size();
            for (size_t i = 0; i < argc - 1; i++) {
                ostream << args[i] << ' ';
            }
            ostream << args[argc - 1] << '\n';
        } else {
            ostream << "Command '" << command << "' not found\n";
        }

        ostream.flush();
    }
};

void prepare() {
    if (std::filesystem::exists("input.txt"))
        return;

    std::ofstream stream;
    stream.open("input.txt", std::ios::out | std::ios::trunc);

    stream << "echo Echo this\n";
    stream << "this should print unknown command\n";
    stream << "exit";

    stream.flush();

    stream.close();
}

int main() {
    prepare();

    std::ifstream istream;
    std::ofstream ostream;

    istream.open("input.txt");
    ostream.open("output.txt", std::ios::out | std::ios::trunc);

    example cmd("(prompt)", ostream, istream);
    cmd.CmdLoop();

    istream.close();
    ostream.close();

    return 0;
}
