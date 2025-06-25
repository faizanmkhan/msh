CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline 
LIBFT_DIR	= ./libft
NAME = minishell

SRCS = myshell.c utils.c parse_env.c init.c parse_input.c \
		additional_functions.c token_helper.c create_command.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(OBJS) -L./libft -lft -o $(NAME) $(LDFLAGS)

.o:.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@cd $(LIBFT_DIR) && $(MAKE) clean
fclean: clean
	rm -f $(NAME)
	@cd $(LIBFT_DIR) && $(MAKE) fclean
re: fclean all

.PHONY: all clean fclean re
