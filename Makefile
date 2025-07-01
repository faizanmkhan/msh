CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline 
LIBFT_DIR	= ./libft
NAME = minishell

SRCS = myshell.c utils.c parse_env.c init.c parse_input.c \
		additional_functions.c token_helper.c create_command.c \
		executor.c signals.c redirection_setup.c find_executable.c \
		builtins.c builtin_cd.c builtin_export.c buildin_env.c pipe_line.c \
		create_commands_operators.c create_commands_words.c execute_single_cmd.c \
		execute_pipeline_cmds.c tokenizing_input.c

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
