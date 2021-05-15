# cmdpp

A Cmd library for C++. Started for learning purposes.

**Note:** Supports only Linux

# Usage

* _Optional_: Create a derived class from `Cmd` class.
* Define your functions in a global scope. Functions should match `CmdFunctionType`. If using a derived class of `Cmd` class, then these functions should not be members of the class.
* Create an object of `Cmd` class or created derived class, and add your functions using `Cmd::AddCommand`.
* Call `CmdLoop` to start the application loop.

## See also
* [Examples](https://www.github.com/umtdg/cmdpp/tree/master/examples)

# TODO
- [ ] Functionality to show command helps
- [ ] One example using all possible features
- [ ] Add comments
- [ ] Add tests
- [ ] Also print stderr in `ShellExecute` (Currently, only stdout is printed)
- [ ] Different output options like error/warning/debug/info

# Completed
- [x] Auto-completion and command history
- [x] Command queue
- [x] Add color option for prompt
