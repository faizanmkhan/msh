#ifndef MYSHELL_H
# define MYSHELL_H

# include <signal.h>
# include <stdio.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include "./libft/libft.h"

extern int g_signal;

typedef enum	e_tok_type
{
	TOK_WORD = 1,
	TOK_SQUOTE,
	TOK_DQUOTE,
	TOK_PIPE,
	TOK_IN_DIRECT,
	TOK_OUT_DIRECT,
	TOK_APPEND,
	TOK_HEREDOC,
	TOK_EOF,
} t_tok_type;

typedef struct s_token
{
	char *value;
	t_tok_type	type;
	struct s_token	*next;
} t_token;

typedef struct s_cmd
{
	char	**args;
	char	*in_file;
	char	*out_file;
	char	*heredoc_delim;
	int		append_mode;
	int		pipe_fd[2];
	struct s_cmd	*next;
} t_cmd;

typedef struct s_env_data
{
	char	*key;
	char	*value;
	struct s_env_data	*next;
} t_env_data;

typedef struct s_shell_data
{
	int			exit_status;
	char		**envp;
	pid_t		pid;
	t_cmd		*head_cmd;
	t_token		*head_token;
	t_env_data	*myenv;
} t_shell_data;

int	is_metachar(char c);
int	is_quote(char c);
void init_shell_data(t_shell_data *myshell, char **envp);
t_env_data *parse_env_var(char *env_str);
void append_env_vars(t_shell_data *myshell, t_env_data *sh_env);
void cleanup_shell(t_shell_data *shell);
void	core_shell_loop(t_shell_data *myshell);
void 	process_input(t_shell_data *myshell, char *input);
t_token	*input_tokenaizer(char *input_str);
t_token	*handle_quote(char *input, int *i, char quote);
char	*extract_string(char *input, int *i);
t_token	*create_token(char *data, t_tok_type type);
void	append_token(t_token **head, t_token **current, t_token *new_token);
t_token	*handle_metachar(char *input, int *i);
t_token	*handle_word(char *input, int *i);
#endif