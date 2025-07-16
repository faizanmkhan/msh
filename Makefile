CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
LIBFT_DIR = ./libft
NAME = minishell

SRCS = \
buildin/builtin_cd.c buildin/builtin_unset.c buildin/builtin_exit.c buildin/builtin_export.c buildin/builtin_echo.c buildin/builtin_cd_utils.c \
cmd/cmd_lst.c cmd/command_utils.c cmd/cmd_creator.c cmd/cmd_echo_arg_setter.c cmd/cmd_echo_arg_setter_utils.c cmd/cmd_arg_setter.c \
env/env_fill.c env/env_helper.c env/find_env_val.c \
executor/executor.c executor/forking.c executor/executor_utils.c executor/executor_builtin.c \
init/init_env.c init/init_shell.c \
myshell.c \
parse/parse_append.c parse/parse_heredoc.c parse/parse_heredoc_utils.c parse/parse_pipe.c parse/parser.c parse/parse_word.c \
redirection/input_redirection.c redirection/output_redirection.c \
signals/signals.c \
token/tokenizer.c token/token_expander.c token/tokenizer_utils.c token/token_lst.c \
utils/remove_quote.c utils/remove_quote_utils.c utils/utils.c utils/utils_error_print.c utils/utils_fd.c utils/utils_restore.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME) $(LDFLAGS)

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
