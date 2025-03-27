# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 16:00:00 by mmusic            #+#    #+#              #
#    Updated: 2025/03/27 18:20:26 by mmusic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = cc
FLAGS = -Wall -Wextra -Werror -g

# Project name and directories
NAME = minishell
OBJ_DIR = obj
LEXER_DIR = lexer
PARSER_DIR = parser
INCLUDES = -I$(LEXER_DIR) -I$(PARSER_DIR)

# Source files by component
LEXER_SRC = \
	lexer.c \
	redirect_utils.c \
	utils.c \
	token_utils.c \
	double_quote_utils.c \
	process_utils.c \
	subtoken_utils.c

PARSER_SRC = 

# Main source file in the root directory
MAIN_SRC = main.c

# Prepend directories to source files
SRC = $(MAIN_SRC) \
	  $(addprefix $(LEXER_DIR)/, $(LEXER_SRC)) \
	  $(addprefix $(PARSER_DIR)/, $(PARSER_SRC))

# Convert source files to object files in the obj directory
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Additional libraries
LIBS = -lreadline

# Phony targets
.PHONY: all clean fclean re

# Default target
all: $(NAME)

# Compile the program
$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBS)

# Create object directories (including nested)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/$(LEXER_DIR)
	mkdir -p $(OBJ_DIR)/$(PARSER_DIR)

# Compile main source files
$(OBJ_DIR)/%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	rm -rf $(OBJ_DIR)

# Clean object files and executable
fclean: clean
	rm -f $(NAME)

# Clean and rebuild
re: fclean all
