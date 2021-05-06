#include "cmdpp/readline.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>

namespace libcmd {

    class Cmd {
    public:
        using ArgType = std::vector<std::string>;
        using CmdFunctionType = std::function<void(const ArgType &, std::ostream &)>;

    protected:
        std::string prompt;
        std::ostream &ostream;
        std::istream &istream;

        bool running;
        bool use_readline;

        std::string exit_command;
        std::unordered_map<std::string, CmdFunctionType> commands;

        Readline readline;

    protected:
        // Main command handler. This needs to be overridden.
        // Only handles 'exit' command.
        void HandleCommands(
                const std::string &command,
                const ArgType &args
        );

        // Called when a command entered with '!' prefix.
        // By default, uses popen and do not redirect stderr.
        virtual void ShellExecute(const std::string &commandline);

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
        explicit Cmd(std::string _prompt) :
            Cmd(std::move(_prompt), "exit") {}

        Cmd(std::string _prompt, std::string _exit_command) :
            Cmd(std::move(_prompt), std::move(_exit_command), std::cout, std::cin) {}

        Cmd(std::string _prompt, std::ostream &_ostream, std::istream &_istream) :
            Cmd(std::move(_prompt), "exit", _ostream, _istream)
        { }

        Cmd(std::string _prompt, std::string _exit_command,
            std::ostream &_ostream, std::istream &_istream) :
            prompt(std::move(_prompt)),
            ostream(_ostream),
            istream(_istream),
            running(false),
            exit_command(std::move(_exit_command)),
            readline(prompt) {
            if (&istream == &std::cin) {
                use_readline = true;
                readline.AddToVocab(exit_command);
            }
        }

        ~Cmd() = default;

        Cmd(const Cmd &) = delete;

        Cmd(Cmd &&) = delete;

        Cmd &operator=(const Cmd &) = delete;

        Cmd &operator=(Cmd &&) = delete;

        void CmdLoop();

        void AddCommand(const std::string &s, CmdFunctionType f);
    };

} //namespace libcmd

