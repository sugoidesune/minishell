CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

SRCS = ft_strlen.c ft_strjoin.c ft_strtrim.c ft_isalpha.c ft_isdigit.c \
ft_isalnum.c ft_isascii.c ft_isprint.c  ft_memset.c ft_bzero.c ft_memcpy.c \
ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
ft_strrchr.c ft_strncmp.c ft_strcmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
ft_atoi.c ft_str_is_num.c ft_printint.c \
ft_calloc.c ft_strdup.c ft_substr.c ft_itoa.c ft_strmapi.c ft_striteri.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c \
ft_printf.c ft_minilib.c ft_printnums.c ft_printstrs.c ft_arraylen.c \
ft_str_append.c 

HEADER = libft.h

OBJS = $(SRCS:.c=.o)
#LAST_SOURCE = $(shell echo $(BONUS_SRCS) | awk '{print $$NF}')

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
