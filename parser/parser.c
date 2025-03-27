#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;
    while ((input = readline("Shell> ")) != NULL) {
        if (strcmp(input, "clear") == 0) {
            rl_clear_history();
            printf("History cleared.\n");
        } else if (strcmp(input, "replace") == 0) {
            rl_replace_line("This is new text", 0);
            rl_redisplay();
            printf("Line replaced.\n");
        } else if (*input) {
            add_history(input);
            printf("You entered: %s\n", input);
        }
        add_history(input);
        free(input);
    }
    return 0;
}