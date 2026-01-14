# NanoShell

A simple shell implementation in C.

## Features

- **Fork**: Creates child processes to execute commands.
- **Path**: Supports command execution from PATH.
- **Execve**: Executes commands using execve system call.
- **Wait**: Waits for child processes to complete.

## Usage

Compile with:
```
gcc nanoshell.c -o nanoshell
```

Run:
```
./nanoshell
```

Type commands at the `?>` prompt. Type `exit` to quit.