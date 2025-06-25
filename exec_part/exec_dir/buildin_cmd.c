#include "../../tokenPars_part/myshell.h"

//TODOS
//2. Strict error handling 
//3. Freeing mem

void	echo_printer(char **args, int n_flag, int i)
{
	while (args[i])
	{
		if (n_flag == 1 && i > 2)
			ft_putchar_fd(' ', 1);
		else if (n_flag == 0 && i > 1)
			ft_putchar_fd(' ', 1);
		if (n_flag == 0 && !args[i + 1])
			ft_putendl(args[i]);
		else
			ft_putstr(args[i]);
		i++;
	}
}

int	ft_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (!args)
		return (-1);
	else if (!args[1])
	{
		ft_putendl_fd("", 1);
		return (0);
	}
	if (ft_strncmp(args[1], "-n", 2) == 0)
	{
		n_flag = 1;
		i++;
	}
	echo_printer(args, n_flag, i);
	return (0);
}

int	ft_cd(char *path)
{
	//char	*cwd;

	//cwd = shell->current_dir;
	if (!path)
		chdir(getenv("HOME"));
	else if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", STD_ERR);
		ft_putendl_fd(path, STD_ERR);
		return (-1); //FIX
	}
	//getcwd(cwd, 1024);
	return (0);
}

int	ft_pwd(char **args)
{
	char	*cwd;

	cwd = NULL;
	if (args[1])
	{
		ft_putendl_fd("pwd: too many arguments", STD_ERR);
		return (-1);
	}
	//ft_putendl_fd(shell->current_dir, 1);
	ft_putendl_fd(getcwd(cwd, 1024), 1);
	return (0);
}
