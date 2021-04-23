# cmdpp

A Cmd library for C++. Started for learning purposes.

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
* [Examples](https://www.github.com/umtdg/cmppp/tree/master/examples)

