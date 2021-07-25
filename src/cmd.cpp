#include "cmdpp/cmd.hpp"
#include "cmdpp/utils.hpp"
#include "cmdpp/color.hpp"

#include <memory>
#include <stdexcept>
#include <string>
#include <array>

namespace cmdpp {

    Cmd::RetCode Cmd::HandleCommands(const std::string &command, const Cmd::ArgType &args) {
        switch (command[0]) {
            case '!':
                ShellExecute(command.substr(1) + " " + Join(args));
                return RET_OK;
            case '?':
                if (useColor) {
                    Colored::PrintColored("[!] ", COLOR_YELLOW, STYLE_DEFAULT, ostream);
                }
                ostream << "Help\n";
                return RET_OK;
        }

        if (commands.find(command) != commands.end()) {
            return commands[command](ostream, args);
        } else {
            if (useColor) {
                Colored::PrintColored(
                        "[!] ",
                        COLOR_RED,
                        STYLE_DEFAULT,
                        ostream);
            }
            ostream << "Command '" << command << "' not found\n" << std::endl;
            return RET_OK;
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

    std::string Cmd::Input() {
        std::string line;

        if (commandQueue.empty()) {
            if (useReadline) {
                line = readline();
            } else {
                ostream << prompt << " ";
                std::getline(istream, line);
            }
        } else {
            line = commandQueue.front();
            commandQueue.pop();
        }

        return line;
    }

    void Cmd::CmdLoop() {
        running = true;

        std::string commandline;

        PreLoop();

        while (running) {
            commandline = Input();
            if (IsEmptyOrWhitespace(commandline))
                continue;

            PreCmd();

            std::vector<std::string> args = Split(commandline);
            std::string command(args[0]);

            args.erase(args.begin());

            if (HandleCommands(command, args) == RET_EXIT) {
                PreExit();

                running = false;
            }

            PostCmd();
        }

        PostLoop();
    }

    void Cmd::AddCommand(const std::string &s, CmdFunctionType f) {
        if (IsEmptyOrWhitespace(s)) return;

        commands[s] = std::move(f);

        // if using readline, add commands to vocabulary
        if (useReadline) {
            readline.AddToVocab(s);
        }
    }

    void Cmd::AddToQueue(const std::string &s) {
        commandQueue.push(s);
    }

} // namespace cmdpp

