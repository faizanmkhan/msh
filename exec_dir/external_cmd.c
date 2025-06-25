#include "../minishell.h"

int	check_for_cmd(char **args, char *path)
{
	pid_t	pid;
	char	*complete_path;
	char	*temp;

	temp = ft_strjoin(path, "/"); //add '/' char on the end of the path
	complete_path = ft_strjoin(temp, args[0]);// merge path and command name
	free(temp);
	if (!complete_path)
		return (-1);
	if (access(complete_path, X_OK) == -1)
	{
		free(complete_path);
		return (-1);
	}
	printf("path: %s\n", complete_path);
	pid = fork();
	if (pid < 0)
	{
		free(complete_path);
		return (-1);
	}
	else if (pid == 0)
		execv(complete_path, args); //in child process execv() command, it will replace current process
	wait(NULL); //prevent zombie process because execv does not return to the code unless it will fail
	free(complete_path);
	return (0);
}

char	**get_env_paths(void) //expand $PATH and separate on ':' character
{
	char	*str;
	char	**paths_list;
	int		i;

	i = 0;
	str = getenv("PATH");
	paths_list = ft_split(str, ':');
	if (paths_list == NULL)
		perror("ERROR!");
	while (paths_list[i])
		i++;
	return (paths_list);
}

int	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		i++;
	while (i >= 0)
		free(paths[i--]);
	free(paths);
	return (0);
}

int	check_absolute_path(char **args)
{
	int	pid;

	if (access(args[0], X_OK) == -1)
	{
		return (-1);
	}
	printf("path: %s\n", args[0]);
	pid = fork();
	if (pid < 0)
	{
		return (-1);
	}
	else if (pid == 0)
		execv(args[0], args);
	return (0);

}

int	external_cmd_exec(char **args, char **paths) //paths already set using get_env_paths()
{
	int	i;

	if (args[0][0] == '/' || args[0][0] == '.') //checks if string starts with '/' or '.' to properly run for example: '/bin/ls' or './a.out' (this ./ is not working perfectly right now)
	{
		check_absolute_path(args); //TODO finish
		return (free_paths(paths));
	}
	i = 0;
	while (paths[i])
	{
		if (check_for_cmd(args, paths[i]) == 0)
			return (free_paths(paths));
		i++;
	}
	free_paths(paths);
	return (-1);
}
