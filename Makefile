CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline 
LIBFT_DIR	= ./libft
NAME = minishell

SRCS = src/builtin_functions/builtin_env.c src/builtin_functions/builtin_cd.c src/builtin_functions/builtin_export.c src/builtin_functions/builtins.c \
src/commands_creation/create_command.c src/commands_creation/create_commands_operators.c src/commands_creation/create_commands_words.c \
src/execution/execute_pipeline_cmds.c src/execution/execute_single_cmd.c src/execution/executor.c src/execution/find_executable.c src/execution/pipe_line.c \
src/execution/redirection_setup.c src/execution/heredoc.c src/initializing/init.c src/initializing/signals.c src/parsing/parse_env.c src/parsing/parse_input.c src/parsing/token_helper.c \
src/parsing/tokenizing_input.c src/utils/additional_functions.c src/utils/utils.c src/myshell.c

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
