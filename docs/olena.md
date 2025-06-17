Notes:

    "" malloc fails?

    Error messages combined on error in pipe

    Expansions are incorrect and segfault on echo $HOME$USER, also try $"HOME"$USER -> HOMEusername

    Ctrl+C + Ctrl+D IOT Core dumped, exit = 130;
    Exit 124124124124 and -124124124 seg fault, done -> exit 124 124 does exit

    SHLVL needs to update on bash or minishell call, and reduce on exit (If no ENV SHLVL 1)
    If no ENV (env -i) segfault

    Heredocs dont expand input when DLIM has any quotes

    If no path, not path to exec (ls, cat, etc...)
    cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory (pwd fail)

     MiniSheLL 🪐 : cat test.x > pre.txt | cat pre.txt | grep s
    🪐 MiniSheLL 🪐 : echo $?
        1

    oltolmac@c2r5p11:~/extra_folders/eval/EvalHell$ export $P="awdawdawd"
    bash: export: `=awdawdawd': not a valid identifier
    oltolmac@c2r5p11:~/extra_folders/eval/EvalHell$ ./minishell 
    🪐 MiniSheLL 🪐 : export $P="awdadawd"
    🪐 MiniSheLL 🪐 : echo $P
    invalid identifiers


    oltolmac@c2r5p11:~/extra_folders/eval/EvalHell$ ulimit -v 10000; ./minishell 
🪐 MiniSheLL 🪐 : export P="$PATH$PATH$PATH"
🪐 MiniSheLL 🪐 : export P="$P$P$P$P$P"
🪐 MiniSheLL 🪐 : export P="$P$P$P$P$P"
🪐 MiniSheLL 🪐 : export P="$P$P$P$P$P"
🪐 MiniSheLL 🪐 : export P="$P$P$P$P$P"
🪐 MiniSheLL 🪐 : Malloc failure in tokenization
(Protect max export value, 1MB is ok)