CC = cc
FLAGS = -Wall -Wextra -Werror -g
NAME = lexer
OBJ_DIR = obj
SRC = lexer.c redirect_utils.c utils.c token_utils.c double_quote_utils.c process_utils.c subtoken_utils.c single_quote_utils.c
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re