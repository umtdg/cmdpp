# cmdpp

A Cmd library for C++. Started for learning purposes.

**Note:** Only Linux and GNU/GCC supported.

# Usage

Create a derived class using `Cmd` class then override `HandleCommands` function.

## Pre/Post Events

### PreLoop and PreCmd
* `PreLoop` is called before command loop started.
* `PreCmd` is called before each `HandleCommands` call.

### PostLoop and PostCmd
* `PostLoop` is called when command loop finished.
* `PostCmd` is called after each `HandleCommands` call.

## See also
* [Examples](https://www.github.com/umtdg/cmdpp/tree/master/examples)

# TODO
- [ ] Add tests
- [ ] Also print stderr in `ShellExecute` (Currently, only stdout is printed)
- [ ] Auto-completion and command history
- [ ] Command queue
- [ ] Functionality to show command helps

