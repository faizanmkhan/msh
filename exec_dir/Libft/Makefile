CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs
#Source files
SRC = srcs/ft_isprint.c \
srcs/ft_strlen.c \
srcs/ft_memset.c \
srcs/ft_bzero.c \
srcs/ft_memmove.c \
srcs/ft_strlcpy.c \
srcs/ft_toupper.c \
srcs/ft_tolower.c \
srcs/ft_strchr.c \
srcs/ft_strrchr.c \
srcs/ft_memchr.c \
srcs/ft_substr.c \
srcs/ft_strmapi.c \
srcs/ft_striteri.c \
srcs/ft_putchar_fd.c \
srcs/ft_putstr_fd.c \
srcs/ft_putendl_fd.c \
srcs/ft_putnbr_fd.c \
srcs/ft_isalnum.c \
srcs/ft_isalpha.c \
srcs/ft_isascii.c \
srcs/ft_isdigit.c \
srcs/ft_memcpy.c \
srcs/ft_itoa.c \
srcs/ft_split.c \
srcs/ft_strjoin.c \
srcs/ft_strtrim.c \
srcs/ft_atoi.c \
srcs/ft_calloc.c \
srcs/ft_memcmp.c \
srcs/ft_strdup.c \
srcs/ft_strlcat.c \
srcs/ft_strncmp.c \
srcs/ft_strnstr.c
OBJ = $(SRC:.c=.o)
NAME = libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(ARFLAGS) $@ $(OBJ)
	@ranlib $@

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re