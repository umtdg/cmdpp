#include <iostream>
#include <vector>
#include <string>

namespace libcmd {

    class Cmd {
    protected:
        std::string prompt;
        bool running;
        std::ostream &ostream;
        std::istream &istream;

    protected:
        // Main command handler. This needs to be overridden.
        // Only handles 'exit' command.
        virtual void HandleCommands(
                const std::string &command,
                std::vector<std::string> &args
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

        /* PRE/POST EVENT FUNCTIONS */

    public:
        // Constructor with single _prompt parameter defaults
        // std::cout and std::cin as output and input streams.
        explicit Cmd(std::string _prompt) :
            prompt(std::move(_prompt)),
            running(false),
            ostream(std::cout),
            istream(std::cin) {}

        Cmd(std::string _prompt, std::ostream &_ostream, std::istream &_istream) :
                prompt(std::move(_prompt)),
                running(false),
                ostream(_ostream),
                istream(_istream) {}

        ~Cmd() = default;

        Cmd(const Cmd &) = delete;

        Cmd(Cmd &&) = delete;

        Cmd &operator=(const Cmd &) = delete;

        Cmd &operator=(Cmd &&) = delete;

        void CmdLoop();
    };

} //namespace libcmd

