#ifndef CMDPP_CMD_HPP
#define CMDPP_CMD_HPP

#include "cmdpp/readline.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <queue>

namespace cmdpp {

    class Cmd {
    public:
        enum RetCode {
            RET_EXIT = 0, // Used for exiting cmd loop
            RET_OK = 1
        };

        using ArgType = std::vector<std::string>;
        using CmdFunctionType = std::function<RetCode(std::ostream &, const ArgType &)>;

    protected:
        std::string prompt;
        std::ostream &ostream;
        std::istream &istream;

        bool running = false;
        bool useReadline = true;
        bool useColor = true;

        std::unordered_map<std::string, CmdFunctionType> commands;
        std::queue<std::string> commandQueue;

        Readline readline;

    protected:
        // Main command handler. This needs to be overridden.
        // Only handles 'exit' command.
        RetCode HandleCommands(
                const std::string &command,
                const ArgType &args
        );

        // Called when a command entered with '!' prefix.
        // By default, uses popen and do not redirect stderr.
        virtual void ShellExecute(const std::string &commandline);

        std::string Input();

        /* PRE/POST EVENT FUNCTIONS */

        // Override these functions when necessary.

        // Called before CmdLoop is started.
        virtual void PreLoop() {}

        // Called after CmdLoop is ended.
        virtual void PostLoop() {}

        // Called before each command.
        // Also applies to commands with prefixes.
        virtual void PreCmd() {}

        // Called after each command.
        virtual void PostCmd() {}

        // Called before exit command is executed
        virtual void PreExit() {}

        /* PRE/POST EVENT FUNCTIONS */

    public:
        // Constructor with single _prompt parameter defaults
        // std::cout and std::cin as output and input streams.
        explicit Cmd(std::string _prompt,
                     bool _useColor = true,
                     std::ostream &_ostream = std::cout,
                     std::istream &_istream = std::cin) :
                prompt(std::move(_prompt)),
                ostream(_ostream),
                istream(_istream),
                useColor(_useColor),
                readline(prompt, _useColor) {
            useReadline = (&istream == &std::cin);
        }

        ~Cmd() = default;

        Cmd(const Cmd &) = delete;

        Cmd(Cmd &&) = delete;

        Cmd &operator=(const Cmd &) = delete;

        Cmd &operator=(Cmd &&) = delete;

        void CmdLoop();

        void AddCommand(const std::string &s, CmdFunctionType f);

        void AddToQueue(const std::string &s);
    };

} //namespace cmdpp

#endif // #ifndef CMDPP_CMD_HPP
