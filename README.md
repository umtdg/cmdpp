# cmdpp

A Cmd library for C++. Started for learning purposes.

**Note:** Supports only Linux

# Usage

* _Optional_: Create a derived class from `Cmd` class.
* Define your functions in a global scope. Functions should match `CmdFunctionType`. If using a derived class of `Cmd` class, then these functions should not be members of the class.
* Create an object of `Cmd` class or created derived class, and add your functions using `Cmd::AddCommand`.
* Call `CmdLoop` to start the application loop.

# Documentation

* [Cmd class](#cmd-class)
* [Readline class](#readline-class)

## Cmd Class
A class used to read commands from either user or a file, execute them and print their output either to console or to a file.

### Type definitions
* `ArgType`: Type of arguments passed to commands
* `CmdFunctionType`: Type of functions added to `commands`

### Constructors
* `Cmd(prompt)`: Initializes a new `Cmd` object with default values for each property.
* `Cmd(prompt, exit_command)`: Initializes a new `Cmd` object with given `prompt` and `exit_command` and with default `ostream` and `istream`.
* `Cmd(prompt, ostream, istream)`: Initializes a new `Cmd` object with given `prompt`, `ostream` and `istream`, defaulting `exit_command` to `exit`.
* `Cmd(prompt, exit_command, ostream, istream)`: Initializes a new `Cmd` object with given `prompt`, `exit_command`, `ostream` and `istream`.

**Note**: Destructor, copy/move constructors and copy/move operators are deleted.

### Properties
* `std::string prompt`: Prompt that will be printed when taking input.
* `std::ostream &ostream`: Stream which is where the output is written. Defaults to `std::cout`
* `std::istream &istream`: Stream which is used to read input. Defaults to `std::cin`
* `bool running`: Application loop's state. This is set to `false` when exiting.
* `bool use_readline`: Flag to use whether `Readline` class to get input or not. This is set to `true` automatically when `std::cin` is given to `istream` member.
* `std::string exit_command`: Command used to exit the loop. By default, this only sets `running` to `false`. Value defaults to `exit`.
* `std::unordererd_map<std::string, CmdFunctionType> commands`: Command list to execute given inputs from.
* `Readline readilne`: An object of `Readline` class to use when `use_readline` is set to `true`.

### Methods
* `HandleCommands`: Handles given input. Sets `running` to `false` when `exit_command` is entered. Otherwise, checks the map `commands`, and executes the corresponding function if exists.
* `ShellExecute`: Executed when a command starting with `!` is entered. Currently, only prints the `stdout` of given command.
* `CmdLoop`: Handles the I/O operations and related pre/post events.
* `AddCommand`: Adds command to `commands` map. Given function should not be a member function.
* `PreLoop`: Called before command loop started.
* `PreCmd`: Called before each `HandleCommands` call.
* `PostLoop`: Called when command loop finished.
* `PostCmd`: Called after each `HandleCommands` call.
* `PreExit`: Called in _exit_command_ before `running` is set to `false`.

## Readline Class
A simple wrapper class for GNU Readline. Supports history and auto-completion.

### Constructors
* `Readline(prompt)`: Initializes a new `Readline` object with given `prompt`.

### Properties
No public or protected properties.

### Methods
* `AddToVocab`: Adds given string to vocabulary. This is used for auto-completion.
* `operator()()`: Operator overload for function call. Used to get input with GNU Readline.

## See also
* [Examples](https://www.github.com/umtdg/cmdpp/tree/master/examples)

# TODO
- [ ] Command queue
- [ ] Functionality to show command helps
- [ ] Add color option for prompt
- [ ] Add more examples (or one big example showing the usage clearly)
- [ ] Add tests
- [ ] Also print stderr in `ShellExecute` (Currently, only stdout is printed)
- [ ] Different output options like error/warning/debug/info

# Completed
- [x] Auto-completion and command history
