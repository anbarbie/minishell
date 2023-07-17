# Minishell

This project involves creating a shell program called Minishell. The shell should provide a command-line interface for users to interact with the operating system. It should support various features, including command execution, input/output redirection, piping, environment variable expansion, and built-in commands.

## Overview

The Minishell program should meet the following requirements:

- Display a prompt when waiting for a new command from the user.
- Implement a working command history feature.
- Search and launch the correct executable based on the PATH variable or provided path.
- Avoid interpreting unclosed quotes or special characters that are not required by the subject, such as backslash (\) or semicolon (;).
- Handle single quotes ('), preventing the shell from interpreting metacharacters within the quoted sequence.
- Handle double quotes (") allowing variable expansion ($), but preventing interpretation of other metacharacters within the quoted sequence.
- Support input and output redirection using the '<' and '>' symbols, respectively.
- Implement here-doc using the '<<' symbol, where the input is read until a line containing the specified delimiter is encountered.
- Support output redirection in append mode using the '>>' symbol.
- Implement pipes ('|') to connect the output of one command to the input of the next command in a pipeline.
- Handle environment variables (e.g., $VAR) and expand them to their respective values.
- Expand '$?' to the exit status of the most recently executed foreground pipeline.
- Handle signal interruptions: ctrl-C, ctrl-D, and ctrl-\ should behave similarly to the bash shell.
- Implement several built-in commands: echo with the -n option, cd with relative or absolute paths, pwd, export, unset, env, and exit.
