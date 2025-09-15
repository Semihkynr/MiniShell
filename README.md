# Minishell

Minishell is a project developed by 42 Turkey students, which aims to replicate a basic Unix shell. The project allows handling user commands, interacting with environment variables, and executing basic shell operations. It provides an in-depth understanding of system programming and Unix/Linux environment principles.

---

## Project Goal

Minishell aims to create a basic shell application that processes user commands, manages environment variables, handles input/output redirection, and runs commands using system calls. The project serves as an introduction to Unix shell behavior and system-level programming.

---

## Core Features

- **Command Execution**: Executes commands entered by the user.
- **Environment Variables**: Supports managing environment variables through commands like `echo`, `cd`, `env`, `export`, and `unset`.
- **Redirection and Pipes**: Implements output redirection (`>`, `>>`) and piping (`|`) to chain commands together.
- **Error Handling**: Provides meaningful error messages for invalid commands or incorrect arguments.
- **Working Directory**: Allows users to change the working directory with the `cd` command.

---

## Usage

Minishell operates directly from the terminal, executing user commands and displaying output in real-time.

### Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/username/minishell.git

2. Build the project:
    ```bash
   make

3.Run the shell:
   ```bash
  ./minishell


### Exit
  To exit Minishell, use the exit command.
