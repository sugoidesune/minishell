NAME = minishell
NAME_BONUS = minishell
CC = cc
CFLAGS = # -Wall -Wextra -Werror

LIBFT_DIR = libft
BUILD_DIR = build
LIBFT_LIB = $(LIBFT_DIR)/libft.a

LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
READLINE_FLAGS = -L. -lreadline

SRCS = gettested.c capture_input_micro.c gnl/error_lib.c gnl/get_next_line.c \
	   gnl/get_next_line_utils.c \
	   listlib/list_lib_1.c listlib/list_lib_2.c \
	   listlib/list_lib_3.c listlib/list_lib_4.c \
	   create_command.c commands_lib.c \
	   path_finder.c builtins.c\

HEADER = micro.h

OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))

all: $(NAME) $(LIBFT_LIB)

$(NAME): $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(READLINE_FLAGS) -o $(NAME)

# what im trying to do with this is compile the libft and the file path_finder.c and output as path program. while reusing the cc and cflags.
path: $(LIBFT_LIB) path_finder.o
	$(CC) $(CFLAGS) path_finder.c gnl/error_lib.c $(LIBFT_FLAGS) -o path

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(BUILD_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(BUILD_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all


.PHONY: all clean fclean re bonus