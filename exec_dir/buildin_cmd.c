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
		//return (kill()); //
	else if (external_cmd_exec(cmds, get_env_paths()) == 0)
		return (0);
	else
		printf("Command not found\n");
	return (-1);
}
