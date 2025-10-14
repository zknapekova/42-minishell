# 42-minishell

The project implements a bash-like shell with support for command history, redirections (>, >>, <, <<), pipes (|), environment variables (including $?), and built-in commands such as `echo`, `export`, `exit`, `cd`, `pwd`, `unset` and `env`. It also correctly handles the execution of external commands, operators '&&', '||', and wildcars (*) for the current working directory.

The program can be started by running 
```
make
```
and executing binary 
```
./minishell
```
which brings up the minishell prompt for command input.
