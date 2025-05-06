In this project only the following functions from external libraries are allowed:
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs
Also the types NULL, and bools true and false are allowed.
Any other functionality must be implemented from scratch.
We have our own libraries of functions check: libft.h, line.h.
Coding guidelines:
No for loops only while.
No ternary operators.
Initalization of variables must be at the start of functions.
assignment and initalization is not allowed in the same line.