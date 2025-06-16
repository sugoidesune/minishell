When a pipe is created, it creates an array with two numbers.
pipe[0] is a file descriptor for the read end.
pipe[1] is a file descriptor for the write end.

These two are connected by the kernel.
When a process writes to the write end pipe[1],
another process can read what was written to pipe[1] by reading at pipe[0].

When chaining multiple processes, we have an array of pipes.
Process A writes to pipes[0][1] (write end), Process B reads from pipes[0][0] (read end) and writes to pipes[1][1] (write end of second pipe). Process C then can
read from pipes[1][0] and so on.