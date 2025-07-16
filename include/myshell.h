/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:52:03 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 13:36:06 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSHELL_H
# define MYSHELL_H

# include <wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stddef.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include "../libft/libft.h"

extern int	g_signal;

typedef enum e_tok_type
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
}	t_tok_type;

typedef struct s_token
{
	char			*value;
	t_tok_type		type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	char			*in_file;
	char			*out_file;
	char			*heredoc_delim;
	int				append_mode;
	int				pipe_fd[2];
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env_data
{
	char				*key;
	char				*value;
	struct s_env_data	*next;
}	t_env_data;

typedef struct s_shell_data
{
	int			syntax_err;
	int			exit_status;
	char		**envp;
	pid_t		pid;
	t_cmd		*head_cmd;
	t_token		*head_token;
	t_env_data	*shell_env;
}	t_shell_data;

t_cmd		*init_command(void);

// =================== BUILTIN FUNCTIONS ===================
int			builtin_cd(t_shell_data *shell, char **args);
int			builtin_echo(char **args);
int			builtin_env(t_shell_data *shell);
int			builtin_export(t_shell_data *shell, char **args);
int			builtin_pwd(void);
int			builtin_exit(t_shell_data *shell, char **args);
int			builtin_unset(t_shell_data *shell, char **args);
int			execute_builtin(t_shell_data *shell, t_cmd *cmd);
int			is_builtin(char *command);
char		*get_env_value(t_shell_data *shell, char *key);
void		set_env_value(t_shell_data *shell, char *key, char *value);
void		unset_env_value(t_shell_data *shell, char *key);
// =================== EXECUTION ===================
int			command_execution(t_shell_data *myshell);
int			execute_single_cmd(t_shell_data *myshell);
int			execute_pipeline(t_shell_data *myshell);
int			setup_redirections(t_cmd *cmd);
int			setup_pipe_if_needed(t_cmd *current);
int			handle_parent_process(pid_t pid, int *prev_fd, t_cmd *current);
void		handle_child_process(t_shell_data *shell,
				t_cmd *current, int prev_fd);
int			setup_heredoc(t_cmd *cmd);
char		*find_executable(t_shell_data *shell, char *command);

// =================== COMMANDS CREATION ===================
t_cmd		*create_cmd_with_token(t_shell_data *myshell);
t_cmd		*init_command(void);
void		handle_argument_word(t_cmd *cmd, t_token *token);
void		handle_word_expand(t_cmd *cmd, t_token *token,
				t_shell_data *myshell);
void		handle_pipe(t_cmd **current);
void		handle_indirection(t_cmd *current, t_token **token);
void		handle_outdirection(t_cmd *current, t_token **token, int mode);
int			handle_heredoc_token(t_cmd *current, t_token **token);

// =================== PARSING ===================
int			is_metachar(char c);
int			is_quote(char c);
t_token		*input_tokenaizer(char *input_str);
t_token		*handle_quote(char *input, int *i, char quote);
t_token		*handle_metachar(char *input, int *i);
t_token		*handle_word(char *input, int *i);
t_token		*create_token(char *data, t_tok_type type);
void		append_token(t_token **head, t_token **current, t_token *new_token);
char		*extract_string(char *input, int *i);
void		free_token(t_token *tokens);

// =================== ENVIRONMENT ===================
t_env_data	*parse_env_var(char *env_str);
void		append_env_vars(t_shell_data *myshell, t_env_data *sh_env);
void		free_env(t_env_data *env);
void		processing_env_expansion(char *s, t_shell_data *myshell,
				char **final_str);
char		*expand_env_value(char *env_s, t_shell_data *myshell);
int			ft_char_pos(char *s, int start, char c);
int			ft_strcmp(const char *str1, const char *str2);
void		free_array(char **array);

// =================== INITIALIZING & SIGNALS ===================
void		init_shell_data(t_shell_data *myshell, char **envp);
//void		cleanup_shell(t_shell_data *shell);
void		core_shell_loop(t_shell_data *myshell);
void		managing_input(t_shell_data *myshell, char *input);
void		set_signals_for_execution(void);
void		free_commands(t_cmd *commands);
void		set_signals_for_parsing(void);
void		syntax_error(t_shell_data *shell);
#endif