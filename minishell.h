#ifndef MINISHELL_H
# define MINISHELL_H

# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2

#include <stdlib.h>
#include "exec_dir/Libft/srcs/libft.h"
#include <unistd.h>
#include <stdio.h>

typedef	struct	s_shell
{
	char	*current_dir;
}	t_shell;

#endif
