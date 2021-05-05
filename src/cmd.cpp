#include "cmdpp/cmd.hpp"
#include "cmdpp/utils.hpp"

#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <algorithm>

namespace libcmd {

    void Cmd::HandleCommands(
            const std::string &command,
            std::vector<std::string> &args
    ) {
		// unused parameter
		(void)args;

        ostream << command << '\n';

        if (command == "exit") {
            running = false;
        } else {
            ostream << "Command '" << command << "' not found\n";
        }

        ostream.flush();
    }

    void Cmd::ShellExecute(const std::string &commandline) {
        std::array<char, 128> buffer{};
        std::unique_ptr<FILE, decltype(&pclose)> pipe(
                popen(commandline.c_str(), "r"),
                pclose
        );

        if (!pipe) {
            throw std::runtime_error("popen() failed");
        }

        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            ostream << buffer.data();
        }

        ostream.flush();
    }

    void Cmd::CmdLoop() {
        running = true;
        std::string commandline;

        PreLoop();

        while (running) {
            ostream << prompt << " ";
            std::getline(istream, commandline);

            if (std::all_of(commandline.begin(), commandline.end(), isspace)) {
                continue;
            }

            PreCmd();

            if (commandline[0] == '!') {
                ShellExecute(commandline.substr(1));

                continue;
            }

            std::vector<std::string> args = split(commandline, ' ');
            std::string command(args[0]);

            args.erase(args.begin());

            HandleCommands(command, args);

            PostCmd();
        }

        PostLoop();
    }

} // namespace libcmd

