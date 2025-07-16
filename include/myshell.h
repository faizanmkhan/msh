/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:18:18 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:58:14 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSHELL_H
# define MYSHELL_H

# include "../libft/libft.h"
# include </usr/include/linux/limits.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define PROMPT "My SHEll~$ "
# define HEREDOC_FILENAME "/tmp/._minishell_heredoc_"
# define SYNTAX_ERR_MSG "syntax error near unexpected token "
# define EOF_ERR_MSG "unexpected EOF while looking for matching"
# define INVALID "not a valid identifier"

# define BAD 1
# define OK 0

extern int	g_exit_code;

enum				e_parse_flags
{
	NORMAL,
	QUOTE,
	DQUOTE,
};

enum				e_separator
{
	WHITESPACE = 1,
	WORD,
	VAR,
	END,
	OUTPUT_REDIR,
	APPEND,
	INPUT_REDIR,
	HEREDOC,
	PIPE,
};

typedef struct s_fds
{
	char			*input_file;
	int				fd_in;
	int				stdin_cpy;
	char			*output_file;
	int				fd_out;
	int				stdout_cpy;
	char			*heredoc_delim;
	bool			heredoc_quotes;
}					t_fds;

typedef struct s_cmd
{
	char			*name;
	char			*path;
	char			**args;
	bool			is_pipe_output;
	int				pipe_fd[2];
	t_fds			*fds;
	struct s_cmd	*nxt;
	struct s_cmd	*prv;
}					t_cmd;

typedef struct s_tok
{
	int				type;
	char			*data;
	char			*data_cpy;
	bool			has_var;
	int				status;
	bool			join;
	struct s_tok	*prv;
	struct s_tok	*nxt;
}					t_tok;

typedef struct s_appdata
{
	char			**envl;
	char			*input;
	t_tok			*head_tok;
	t_cmd			*head_cmd;
	pid_t			pid;
}					t_appdata;

// main.c
void		exit_minishell(t_appdata *appdata, int exit_code);

// parser.c
bool		parse_user_input(t_appdata *appdata);

// parser_word.c
void		parse_word(t_cmd **head_cmd, t_tok **head_tok);

// parser_input_redirection.c
void		parse_input_redirection(t_cmd **head_cmd, t_tok **head_tok);
bool		remove_input_file_ref(t_fds *fds);
bool		remove_output_file_ref(t_fds *fds);

// parser_append.c
void		parse_append(t_cmd **head_cmd, t_tok **head_tok);

// parser_output_redirection.c
void		parse_output_redirection(t_cmd **head_cmd, t_tok **head_tok);

// parser_heredoc.c
void		parse_heredoc(t_appdata *appdata, t_cmd **last_cmd,
				t_tok **token_lst);

// parser_heredoc_utils.c
char		*heredoc_filename(void);
char		*find_delimiter(char *str, bool *has_quotes);
char		*expanded_line(t_appdata *appdata, char *line);
char		*join_words_with_spaces(char **tab);

// parser_pipe.c
void		parse_pipe(t_cmd **head_cmd, t_tok **head_tok);

// utils.c
void		ft_free_tab(char **tab);
void		free_ptr(void *ptr);
int			ft_is_whitespace(int c);
int			is_only_whitespace(char *input);
int			ft_isspace(int c);
void		close_pipe_fds(t_cmd *cmd);
void		free_str_tab(char **tab);
void		print_error(void);
void		free_fds(t_fds *fds);
void		close_fds(t_cmd *cmd, int with_restore);
bool		use_backup_fd(t_fds *fds);
int			valid_fds(t_fds *fds);
int			valid_appdata(t_appdata *appdata);
bool		redirect(t_fds *fds);
int			wrapper_close(int fd);
int			wrapper_close_pipe(int *fd);
int			ft_chdir(char *path);
char		*find_path(char **envp, char *cmd, int i);
int			check_command_not_found(t_cmd *cmd, int code);
int			valid_command(t_cmd *cmd, int *exit_code);
bool		restore_fds(t_fds *fds);

// utils_print_error.c
char		*ft_strextend(char *str, char *extend);
int			ft_print_cmd_error(char *cmd, char *cmd_arg, char *msg,
				int exit_code);
void		ft_print_error(char *msg, char *symbol, int quotes);

// initializer.c
bool		init_appdata(t_appdata *appdata, int argc, char **argv,
				char **envp);
void		free_appdata(t_appdata *appdata, bool clean_history);
void		init_fds(t_cmd *cmd);

// env.c
bool		change_envl(t_appdata *appdata, char *key, char *value);
bool		is_valid_env_key(char *key);
bool		init_envl(t_appdata *appdata, char **envp);

// env_helper.c
bool		update_existing_envl(t_appdata *appdata, char *key, char *value);
char		*create_new_envl_entry(char *key, char *value);
char		**expand_envl_list(char **envl, int size);
bool		add_new_envl(t_appdata *appdata, char *key, char *value);
char		*clean_var_heredoc(char *str, int var_i);

// env_filler.c
bool		fill_env_var_val(t_tok *tok, char *val, int i);
char		*fill_env_var_val_heredoc(char *str, char *val, int i);

// tokenizer.c
int			tokenize(t_appdata *appdata, char *input);

// tokenizer_expander.c
void		expand_env_vars(t_appdata *appdata);
char		*expand_heredoc_vars(t_appdata *appdata, char *str);

// tokenizer_utils.c
int			get_separator(char *s);
void		update_flag(int *flag, char s);

// quotes_remover.c
int			remove_quotes_in_toks(t_appdata *appdata);

// quotes_remover_utils.c
bool		should_change_status(t_tok *tok, int *i);

// env_finder.c
char		*get_env_var_val(t_appdata *appdata, t_tok *tok, char *str);
int			key_length(char *str);

// tok_lst.c
t_tok		*new_tok(char *str, char *str_cpy, int type, int status);
void		add_back_tok(t_tok **head, t_tok *new_tok);
void		del_tok(t_tok *tok_to_del, void (*del)(void *));
void		del_all_toks(t_tok **head, void (*del)(void *));

// tok_lst_helper.c
t_tok		*insert_lst_between(t_tok **head, t_tok *to_del, t_tok *to_add);

// cmd_lst.c
t_cmd		*new_cmd(void);
void		add_back_cmd(t_cmd **head, t_cmd *new_cmd);
t_cmd		*last_cmd(t_cmd *cmd);
void		del_cmd(t_cmd *cmd, void (*del)(void *));
void		del_all_cmds(t_cmd **head, void (*del)(void *));

// cmd_args_setter.c
int			set_cmd_args(t_cmd *cmd, t_tok **head_tok);

// cmd_echo_args_setter.c
int			create_echo_args(t_cmd *cmd, t_tok **head_tok);
int			update_echo_args(t_cmd *cmd, t_tok **head_tok);

// cmd_echo_args_setter_utils.c
int			args_echo_size(t_tok *tok);
char		*join_echo_args(t_tok **tok);
char		**recreate_echo_args(char **args, int size, t_cmd *cmd,
				t_tok **head_tok);
void		clear_empty_echo_vars(t_tok **tok);

// cmd_generator.c
void		generate_cmd_list(t_appdata *appdata, t_tok *tok);

// executor.c
int			execute(t_appdata *appdata);

// forking.c
int			create_children(t_appdata *appdata);
// executor_builtin.c
int			execute_builtin(t_appdata *appdata, t_cmd *cmd);

// builtin_export.c
int			builtin_export(t_appdata *appdata, t_cmd *cmd);

// builtin_echo.c
int			builtin_echo(t_cmd *cmd);

// builtin_env.c
int			builtin_env(t_appdata *appdata);

// builtin_unset.c
int			builtin_unset(t_appdata *appdata, t_cmd *cmd);
int			look_env(char *arg, t_appdata *appdata);

// builtin_exit.c
int			builtin_exit(t_appdata *appdata, t_cmd *cmd);

// bool builtin_pwd
bool		builtin_pwd(void);
// builtin_cd
bool		builtin_cd(t_appdata *appdata, char **argv);
int			swap_pwd(char *dir, t_appdata *appdata, char *curr_dir);
char		*look_env_value(char *argv, char **new_env);

// builtin_cd_utils.c
int			only_oldpwd_setted(t_appdata *appdata, char *temp);
int			only_pwd_setted(t_appdata *appdata, char *temp, char *pwd);
int			pwd_oldpwd_setted(t_appdata *appdata, char *temp);
int			swap_pwd(char *dir, t_appdata *appdata, char *curr_dir);

// signals.c
void		set_signals_for_parsing(void);
void		set_signals_for_execution(void);

/// executor_utils.c
int			execute_command(t_appdata *appdata, t_cmd *cmd);

#endif
