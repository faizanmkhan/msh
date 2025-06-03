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

typedef struct s_shell
{
	char	*current_dir;
}	t_shell;

char	**get_env_paths(void);
int		external_cmd_exec(char **args, char **paths);
int		check_for_cmd(char **cmds, char *path);
int		check_is_buildin(char **cmds, t_shell *shell);
int		check_for_operators(char **cmds, t_shell *shell);

#endif
