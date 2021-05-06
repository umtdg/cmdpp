#include "cmdpp/cmd.hpp"
#include "cmdpp/utils.hpp"

#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <algorithm>
#include <utility>

namespace libcmd {

    void Cmd::HandleCommands(const std::string &command, const Cmd::ArgType &args) {
        if (command == exit_command) {
            PreExit();

            running = false;
        } else if (commands.find(command) != commands.end()) {
            commands[command](args, ostream);
        } else {
            ostream << "Command '" << command << "' not found\n";
        }
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
            if (use_readline) {
                commandline = readline();

                if (commandline.empty())
                    continue;
            } else {
                ostream << prompt << " ";
                std::getline(istream, commandline);

                if (libcmd::is_empty_or_whitespace(commandline)) {
                    continue;
                }
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

    void Cmd::AddCommand(const std::string &s, CmdFunctionType f) {
        commands[s] = std::move(f);

        // if using readline, add commands to vocabulary
        if (use_readline) {
            readline.AddToVocab(s);
        }
    }

} // namespace libcmd

