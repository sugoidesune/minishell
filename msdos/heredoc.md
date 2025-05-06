Your understanding is mostly correct, but there are a few crucial details and nuances, especially regarding expansion and how the input is provided to the command:

*   **Multiline Input**: Yes, a heredoc (`<< DELIMITER`) reads subsequent lines of input until a line containing exactly `DELIMITER` (with no other characters and followed by a newline) is encountered.
*   **Expansion**: You are correct that variable expansion (like `$VAR` or `$?`) typically occurs within the heredoc content. However, a key rule is that if any part of the `DELIMITER` on the initial command line was quoted (e.g., `<< 'EOF'`, `<< "EOF"`), then no expansion is performed on the heredoc content. If the `DELIMITER` was unquoted, expansion happens as usual.
*   **Delimiter Removal**: Correct. The starting line with `<< DELIMITER` and the final line containing only `DELIMITER` are not part of the content passed to the command.
*   **Usage/Integration**: This is where the main difference lies. The processed heredoc content isn't just treated as a string argument. It becomes the standard input (`stdin`) for the command it's associated with. The common way to implement this is:
    1.  Read the heredoc lines (performing expansion only if the delimiter was unquoted).
    2.  Write this processed content to a temporary file (or potentially a pipe).
    3.  When executing the command, use `dup2()` to redirect the command's `stdin` (file descriptor 0) to read from that temporary file (or pipe).
    4.  Clean up (delete) the temporary file after the command finishes.

**In summary:**

*   You need to parse the `<<` and the `DELIMITER`, noting if the delimiter was quoted.
*   Read input lines until the delimiter is found.
*   Perform expansion only if the delimiter was unquoted.
*   Store the resulting content (likely in a temporary file).
*   Redirect the command's `stdin` to this temporary storage before executing it.

Your list covers the main functional steps involved. Here's a breakdown with considerations based on your project's likely structure and common shell behavior:

1.  **Parse raw string and check if expansion should be performed**: Correct. This happens during the main parsing phase (parser). You need to identify the `<<` operator and the subsequent delimiter token. You also need to check if the delimiter token itself contained quotes (e.g., `<< 'EOF'` vs `<< EOF`). Store the delimiter (without the quotes) and a flag indicating if expansion should occur.
2.  **A function that can perform expansion**: Correct. This function will be called line-by-line on the heredoc input if the delimiter was unquoted. You might be able to reuse or adapt your existing `expand_string` function.
3.  **A function that reads input until the delimiter**: This is more accurate than "removes the delimiter". You need a loop that reads lines of input (using `readline` or `get_next_line`) until a line matching the delimiter exactly is found. This loop incorporates step 2 (conditional expansion) and step 4 (writing).
4.  **A function that saves heredoc content to a file**: Correct. This involves generating a unique temporary filename (often in `/tmp`), opening it, writing the processed lines (from step 3) to it, and closing it. This whole process (steps 3 & 4 combined) should happen *before* command execution begins. Your `architecture.md` mentions `make_heredoc`.
5.  **A function that redirects command input**: Correct. During command execution (`execute_command` or its redirection handling part like `dispatch_redirections`), if a heredoc was processed for this command, you'll open the corresponding temporary file for reading and use `dup2()` to make the command's standard input read from this file.
6.  **A function that deletes the heredoc file**: Correct. After the command (or potentially the entire pipeline) finishes execution, you need to `unlink()` the temporary file. Your `architecture.md` mentions `remove_heredoc`.

**Key Considerations/Potential Missing Points:**

*   **Timing**: Heredoc processing (reading input, creating the temp file) must happen *before* any commands in the pipeline are forked or executed.
*   **Signal Handling (`SIGINT`/`Ctrl+C`)**: Standard shells allow `Ctrl+C` to interrupt the heredoc input process without terminating the shell. You'll need specific signal handling active only during the heredoc reading loop (step 3).
*   **EOF Handling**: What happens if the input stream ends (`EOF`, `Ctrl+D`) before the delimiter is found? Bash usually prints a warning.
*   **Temporary Filenames**: Ensure your method for generating temporary filenames is robust enough to avoid collisions if multiple heredocs are used.
*   **Multiple Heredocs**: Your design should handle multiple heredocs within a single command line correctly (e.g., `cat << EOF1 << EOF2`). Each needs its own temporary file.

Your list provides a solid foundation. Integrating these steps correctly with the timing, signal handling, and existing execution flow (using `dup2`) is crucial.


Timing Expansions:

The correct behavior, matching standard shells like Bash, is that heredoc processing and expansion happen before any commands in the pipeline are executed.

Process flow:
1. Shell reads the entire command line: `command1 | command2 << EOF`
2. Shell identifies the heredoc `<< EOF` associated with command2
3. Shell reads the heredoc input lines from the user
4. Shell performs expansion on these lines (assuming EOF wasn't quoted). It looks up `COUNT` in the current shell environment, where `COUNT=1`. The expanded content (containing `1`) is stored in a temporary file
5. Shell sets up the pipeline
6. Shell executes command1. If command1 modifies `COUNT` (e.g., via `export COUNT=2`), that change occurs now
7. Shell executes command2, with its standard input redirected to the temporary file created in step 4 (which contains the value `1`)

Therefore, the value of `COUNT` expanded within the heredoc should be `1`, reflecting the variable's value before the pipeline started executing.
 