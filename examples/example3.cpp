// Example using a map to store command functions and calling
// them in HandleCommands

#include "cmdpp/cmd.hpp"

#include <map>
#include <vector>

class example : public libcmd::Cmd {
protected:
    typedef void (example::*cmdFunctionPtr)(std::vector<std::string> &args);

    std::map<std::string, cmdFunctionPtr> cmdFunctions;

public:
    explicit example(std::string _prompt) :
            libcmd::Cmd(std::move(_prompt)) {
        // add commands here or make AddCommand
        // function public and add functions outside
        // of class
        AddCommand("echo", &example::echo);
        AddCommand("exit", &example::exit);
    }

protected:
    // Function used to add commands to map.
    // Can be made virtual to support inheritance
    // with more flexibility.
    void AddCommand(const std::string &name, cmdFunctionPtr function) {
        cmdFunctions[name] = function;
    }

    /* Cmd functions */
    void echo(std::vector<std::string> &args) {
        for (const std::string &arg : args) {
            ostream << arg << ' ';
        }
        ostream << '\n';
    }

    void exit(std::vector<std::string> &args) {
        // insert any code to run before exit here

        running = false;
    }
    /* Cmd functions */

    // Basically, checks if command is in the map, and then
    // calls the corresponding function.
    void HandleCommands(const std::string &command, std::vector<std::string> &args) override {
        if (cmdFunctions.find(command) != cmdFunctions.end()) {
            (this->*(cmdFunctions[command]))(args);
        } else {
            ostream << "Command '" << command << "' not found\n";
        }
    }
};

int main() {
    example cmd("(prompt)");
    cmd.CmdLoop();

    return 0;
}
