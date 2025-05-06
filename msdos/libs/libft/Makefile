# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/20 12:30:33 by rgiambon          #+#    #+#              #
#    Updated: 2024/11/14 10:35:43 by rgiambon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strlcpy.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
OBJS = ${SRCS:.c=.o}
HEADERS = libft.h
BONUS_SRCS = ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstlast_bonus.c ft_lstsize_bonus.c ft_lstadd_front_bonus.c ft_lstiter_bonus.c ft_lstnew_bonus.c ft_lstclear_bonus.c ft_lstmap_bonus.c
BONUS_OBJS = ${BONUS_SRCS:.c=.o}
BONUS_MARKER = .bonus

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	@rm -f $(BONUS_MARKER)

bonus: $(BONUS_MARKER)

$(BONUS_MARKER): $(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
	@touch $(BONUS_MARKER)

%.o: %.c Makefile $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS) $(BONUS_MARKER)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SILENT: 
