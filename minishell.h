#ifndef MINISHELL_H
# define MINISHELL_H

# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2

# include <stdlib.h>
# include "exec_dir/Libft/srcs/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "exec_dir/gnl/get_next_line.h"

typedef struct s_shell
{
	char	*current_dir;
	int	saved_stdin;
	int	saved_stdout;
}	t_shell;

typedef struct s_cmd
{
	char			**args;
	char			*input_file;
	char			*output_file;
	int				append_mode;
	char			*heredoc_delimiter;
	struct s_cmd	*next;
} t_cmd;

char	**get_env_paths(void);
int		external_cmd_exec(char **args, char **paths);
int		check_for_cmd(char **cmds, char *path);
int		check_is_buildin(char **cmds, t_shell *shell);
int		check_for_operators(char **cmds, t_shell *shell);
int		piped_commands(int *pipes, char *input);
int		*pipe_counter(char *str);
char		*clear_str(char *str);
int		check_cmd(t_cmd *cmd, t_shell *shell); 
int		pipe_loop(t_cmd *cmds, t_shell *shell);
int	input_redir(t_cmd *cmd, t_shell *shell, char *file_path);
int	output_redir(t_cmd *cmd, t_shell *shell, char *file_path, int append_mode);
void	ft_putstr(char *s);
void	ft_putendl(char *s);
int	reset_redir(t_shell *shell);

#endif
