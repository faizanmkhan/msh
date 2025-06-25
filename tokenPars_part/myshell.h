#ifndef MYSHELL_H
# define MYSHELL_H

# include <signal.h>
# include <stdio.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "./libft/libft.h"

# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2

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
	int			cmd_index;
	int			saved_stdin;
	int			saved_stdout;
	pid_t		pid;
	t_cmd		*head_cmd;
	t_token		*head_token;
	t_env_data	*shell_env;
} t_shell_data;

int	is_metachar(char c);
int	is_quote(char c);
void init_shell_data(t_shell_data *myshell, char **envp);
t_env_data *parse_env_var(char *env_str);
void append_env_vars(t_shell_data *myshell, t_env_data *sh_env);
void cleanup_shell(t_shell_data *shell);
void	core_shell_loop(t_shell_data *myshell);
void 	managing_input(t_shell_data *myshell, char *input);
t_token	*input_tokenaizer(char *input_str);
t_token	*handle_quote(char *input, int *i, char quote);
char	*extract_string(char *input, int *i);
t_token	*create_token(char *data, t_tok_type type);
void	append_token(t_token **head, t_token **current, t_token *new_token);
t_token	*handle_metachar(char *input, int *i);
t_token	*handle_word(char *input, int *i);
void	free_token(t_token *tokens);
t_cmd	*create_cmd_with_token(t_shell_data *myshell);

//exec
char	**get_env_paths(void);
int		external_cmd_exec(char **args, char **paths);
int		check_for_cmd(char **cmds, char *path);
int		check_is_buildin(char **cmds, t_shell_data *shell);
int		check_for_operators(char **cmds, t_shell_data *shell);
int		piped_commands(int *pipes, char *input);
int		*pipe_counter(char *str);
char		*clear_str(char *str);
int		check_cmd(t_cmd *cmd, t_shell_data *shell); 
int		pipe_loop(t_cmd *cmds, t_shell_data *shell);
int	input_redir(t_cmd *cmd);
int	output_redir(t_cmd *cmd, int append_mode);
void	ft_putstr(char *s);
void	ft_putendl(char *s);
int	reset_redir(t_shell_data *shell);
void	echo_printer(char **args, int n_flag, int i);
int	ft_echo(char **args);
int	ft_cd(char *path);
int	ft_pwd(char **args);
#endif
