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


## 🚀 Contributors

| Avatar | Name | Role | GitHub |
|--------|------|------|--------|
| <img src="https://github.com/ilyassealdidi.png" width="30"> | Ilyasse Aldidi | Command Parsing | [@ilyassealdidi](https://github.com/ilyassealdidi) |
| <img src="https://github.com/aitelkadi.png" width="30"> | Abdelhalim Aitelkadi | Command Execution | [@aitelkadi](https://github.com/aitelkadi) |

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
