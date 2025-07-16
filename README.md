# Minishell

Minishell is a simplified Unix shell implemented in C. It provides basic shell functionalities such as executing commands, handling pipes, redirections, and environment variables.

## Features

- Command execution (built-in and external)
- Input/output redirection (`>`, `<`, `>>`)
- Pipes (`|`)
- Environment variable expansion
- Built-in commands: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`
- Signal handling (e.g., `Ctrl+C`, `Ctrl+D`)

## Getting Started

### Prerequisites

- GCC or Clang
- Make
- Unix-like environment (Linux, macOS)

### Building

```sh
make
```

### Running

```sh
./minishell
```

## Usage

Type commands as you would in a standard shell:

```sh
minishell$ ls -l | grep minishell > output.txt
minishell$ export PATH=$PATH:/custom/path
minishell$ cd ..
```

## Project Structure

- `src/` — Source code files
- `include/` — Header files
- `Makefile` — Build instructions

## Authors

- [Ilyasse Aldidi](https://github.com/ilyassealdidi)
- [Abdelhalim Aitelkadi](https://github.com/aaitelka)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.