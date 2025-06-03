#include "../minishell.h"

//TODOS
//1. Support for absolute path eg. (/bin/dir1/child_dir/filename.file
//2. Strict error handling 
//3. Freeing mem
//4. 'global' variable support for export and unset functions.
//5. Actually kill cmd i guess (kill_all func, that kills each pid from pid array in struct maybe??)

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
	while (args[i])
	{
		if (n_flag == 1 && i > 2)
			ft_putchar_fd(' ', 1);
		else if (n_flag == 0 && i > 1)
			ft_putchar_fd(' ', 1);
		if (n_flag == 0 && !args[i + 1])
			ft_putendl_fd(args[i], 1);
		else
			ft_putstr_fd(args[i], 1);
		i++;
	}
	return (0);
}

int	ft_cd(char *path, t_shell *shell)
{
	char	*cwd;

	cwd = shell->current_dir;
	if (!path)
		chdir(getenv("HOME"));
	else if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", STD_ERR);
		ft_putendl_fd(path, STD_ERR);
		return (-1);
	}
	getcwd(cwd, 1024);
	return (0);
}

int	perform_buildin(char **cmds, char *path)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("fork failed");
	else if (pid == 0)
		execv(path, cmds);
	else
		printf("Parent\n");
}

int	ft_pwd(char **args, t_shell *shell)
{
	if (args[1])
	{
		ft_putendl_fd("pwd: too many arguments", STD_ERR);
		return (-1);
	}
	ft_putendl_fd(shell->current_dir, 1);
	return (0);
}

int	check_is_buildin(char **cmds, t_shell *shell)
{
	char	*path;

	if (!cmds || !cmds[0] || !shell || !shell->current_dir)
		return (-1);
	if (ft_strncmp(cmds[0], "echo", 4) == 0)
		return (ft_echo(cmds));
	else if (ft_strncmp(cmds[0], "cd", 2) == 0)
		return (ft_cd(cmds[1], shell));
	else if (ft_strncmp(cmds[0], "pwd", 3) == 0)
		return (ft_pwd(cmds, shell));
	//else if (ft_strncmp(cmds[0], "export", 6) == 0)
	//	return (perform_buildin(cmds, path));
	//else if (ft_strncmp(cmds[0], "unset", 5) == 0)
	//	return (perform_buildin(cmds, path));
	//else if (ft_strncmp(cmds[0], "env", 3) == 0)
	//	return (perform_buildin(cmds, path));
	//else if (ft_strncmp(cmds[0], "exit", 4) == 0)
		//return (kill(getpid));
	else if (external_cmd_exec(cmds, get_env_paths()) == 0)
		return (0);
	else
		printf("Command not found\n");
	return (-1);
}

int	check_for_operators(char **cmds, t_shell *shell)
{
	int		i;
	int		j;
	int		count;
	int		operator_flag;

	i = 0;
	j = 0;
	operator_flag = 0;
	/*while (cmds[i])
	{
		found = ft_strchr(cmds[i], '"');
		if (found != NULL)
		{
			first_occ = found - cmds[i];
			if (first_occ < ft_strchr(cmds[i], '|') - cmds[i])
				while (cmds[i][first_occ + j])
					if (cmds[i][first_occ + j] == '"')
						if ((first_occ + j) > ft_strchr(cmds[i], '|') - cmds[i])
	*/
	count = 0;
	while (cmds[i])
	{
		printf("%c\n", cmds[i][j]);
		if (!cmds[i][j])
		{
			i++;
			j = 0;
			continue ;
		}
		else if ((cmds[i][j] == 34 || cmds [i][j] == 39) && operator_flag == 1)
		{ printf("count++\n");
			count++;}
		else if (cmds[i][j] == '|' && !operator_flag)
			operator_flag = 1;
		j++;
	}
	printf("op flag: %d\ncount: %d\n", operator_flag, count);
	if (count % 2 == 0 && count > 0)
		printf("pipe inside quotes! %d\n", count);
	/* okey so: 
	 * check for the operator sign, then check if this operator is in between quotes
	 * 	1. count all quotes
	 * 	2. check how many quotes is after operator character
	 * 		example: 4 quotes, 2 quotes after index of '|', that means '|' isn't soruunded by any quote
	}*/
	return (check_is_buildin(cmds, shell));
}
